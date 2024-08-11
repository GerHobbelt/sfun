#include <sfun/type_list.h>
#include <gtest/gtest.h>

using namespace sfun;

struct Foo {};

TEST(TypeList, At)
{
    auto list = type_list<int, double, Foo>{};
    ASSERT_EQ(list.size(), 3);
    EXPECT_TRUE((std::is_same_v<decltype(list.template at<0>())::type, int>));
    EXPECT_TRUE((std::is_same_v<decltype(list.template at<1>())::type, double>));
    EXPECT_TRUE((std::is_same_v<decltype(list.template at<2>())::type, Foo>));
}

TEST(TypeList, Get)
{
    auto list = type_list<int, double, Foo>{};
    ASSERT_EQ(list.size(), 3);
    EXPECT_TRUE((std::is_same_v<decltype(get<0>(list))::type, int>));
    EXPECT_TRUE((std::is_same_v<decltype(get<1>(list))::type, double>));
    EXPECT_TRUE((std::is_same_v<decltype(get<2>(list))::type, Foo>));
}

TEST(TypeList, ToTuple)
{
    auto list = type_list<int, double, Foo>{};
    EXPECT_TRUE((std::is_same_v<to_tuple_t<decltype(list)>, std::tuple<int, double, Foo>>));
}

TEST(TypeList, Slice)
{
    auto list = type_list<int, double, Foo>{};
    EXPECT_TRUE((std::is_same_v<decltype(list.template slice<0, 2>()), type_list<int, double>>));
    EXPECT_TRUE((std::is_same_v<decltype(list.template slice<1, 2>()), type_list<double, Foo>>));
    EXPECT_TRUE((std::is_same_v<decltype(list.template slice<0, list.size()>()), type_list<int, double, Foo>>));
}

TEST(TypeList, Compare)
{
    auto list = type_list<int, double, Foo>{};
    EXPECT_TRUE((list == type_list<int, double, Foo>{}));
    EXPECT_FALSE((list == type_list<double, double, Foo>{}));
    EXPECT_FALSE((list == type_list<int, double>{}));

    constexpr auto list2 = type_list<int, double, Foo>{};
    static_assert(list2 == type_list<int, double, Foo>{});
}

TEST(TypeList, ConstructFromTuple)
{
    auto list = type_list<int, double, Foo>{};
    EXPECT_TRUE((list == type_list{std::tuple<int, double, Foo>{}}));
    EXPECT_FALSE((list == type_list{std::tuple<double, Foo>{}}));
}
