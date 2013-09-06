#include <iostream>

#include <boost/mpl/unique.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>

#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/container/map/map_fwd.hpp>
#include <boost/fusion/include/map_fwd.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/include/has_key.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/include/at_key.hpp>

#include <boost/type_traits/is_same.hpp>

/***************************************************************************/

template<typename... Types>
struct impl_container {
	template<typename... Args>
	impl_container(const Args&... args)
		:cont(boost::fusion::make_pair<Types>(args...)...)
	{}

	template<typename Iface>
	Iface& get() {
		enum { value = boost::fusion::result_of::has_key<cont_type, Iface>::value };
		static_assert(value, "doesn't contain implementation with this type");
		return checker_helper<void, value>::template apply<Iface>(cont);
	}

	template<typename Iface>
	const Iface& get() const {
		enum { value = boost::fusion::result_of::has_key<cont_type, Iface>::value };
		static_assert(value, "doesn't contain implementation with this type");
		return checker_helper<void, value>::template apply<Iface>(cont);
	}

private:
	template<typename, bool>
	struct checker_helper;

	template<typename Fake>
	struct checker_helper<Fake, true> {
		template<typename T, typename Map>
		static const T& apply(const Map& map) {
			return boost::fusion::at_key<T>(map);
		}

		template<typename T, typename Map>
		static T& apply(Map& map) {
			return boost::fusion::at_key<T>(map);
		}
	};
	template<typename Fake>
	struct checker_helper<Fake, false> {
		template<typename T, typename Map>
		static const T& apply(const Map&) {}

		template<typename T, typename Map>
		static T& apply(Map&) {}
	};

private:
	using cont_type = boost::fusion::map<
		boost::fusion::pair<Types, Types>...
	>;

	cont_type cont;

private:
	using _1 = boost::mpl::placeholders::_1;
	using _2 = boost::mpl::placeholders::_2;

	using types = boost::mpl::vector<Types...>;
	static_assert(
		 boost::mpl::size<
			typename boost::mpl::unique<types, boost::is_same<_1, _2>>::type
		 >::value == sizeof...(Types)
		,"only unique types allowed"
	);
};

/***************************************************************************/

struct type1 {
	int v;
	type1(int v)
		:v(v)
	{}
	int m() const { return v+v; }
};
struct type2 {
	int v;
	type2(int v)
		:v(v)
	{}
	int m() const { return v+v+v; }
};
struct type3 {
	int v;
	type3(int v)
		:v(v)
	{}
	int m() const { return v+v+v+v; }
};

struct type4 {
	int v;
	type4(int v)
		:v(v)
	{}
	int m() const { return v+v+v+v+v; }
};

/***************************************************************************/

int main() {
	//impl_container<type1, type1> cont(2); // static assertion: 'only unique types allowed'
	impl_container<type1, type2, type3> cont(2);

	std::cout << cont.get<type1>().m() << std::endl; // 4
	std::cout << cont.get<type2>().m() << std::endl; // 6
	std::cout << cont.get<type3>().m() << std::endl; // 8
	//std::cout << cont.get<type4>().m() << std::endl; // static assertion: 'doesn't contains implementation with this type'
}

/***************************************************************************/
