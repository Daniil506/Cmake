// Copyright 2026 Daniil506

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

#include "lib_queue/queue.h"

TEST(QueueTest, InitialState) {
    Queue<int> q(5);

    EXPECT_TRUE(q.is_empty());
    EXPECT_FALSE(q.is_full());
    EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, PushPopBasic) {
    Queue<int> q(3);

    q.push(10);
    q.push(20);

    EXPECT_FALSE(q.is_empty());
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.front(), 10);

    EXPECT_EQ(q.pop(), 10);
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 20);

    EXPECT_EQ(q.pop(), 20);
    EXPECT_TRUE(q.is_empty());
}

TEST(QueueTest, CircularBufferBehavior) {
    Queue<int> q(3);

    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_TRUE(q.is_full());

    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);

    q.push(4);
    q.push(5);

    EXPECT_TRUE(q.is_full());
    EXPECT_EQ(q.front(), 3);

    EXPECT_EQ(q.pop(), 3);
    EXPECT_EQ(q.pop(), 4);
    EXPECT_EQ(q.pop(), 5);

    EXPECT_TRUE(q.is_empty());
}

TEST(QueueTest, CopyConstructor) {
    Queue<int> q(3);

    q.push(1);
    q.push(2);
    q.pop();
    q.push(3);
    q.push(4);

    Queue<int> q_copy = q;

    EXPECT_EQ(q_copy.size(), q.size());
    EXPECT_TRUE(q_copy.is_full());

    EXPECT_EQ(q_copy.pop(), 2);
    EXPECT_EQ(q_copy.pop(), 3);
    EXPECT_EQ(q_copy.pop(), 4);

    EXPECT_TRUE(q_copy.is_empty());
    EXPECT_EQ(q.front(), 2);
}

TEST(QueueTest, Exceptions) {
    Queue<int> q(2);

    EXPECT_THROW(q.pop(), std::out_of_range);
    EXPECT_THROW(q.front(), std::out_of_range);

    q.push(10);
    q.push(20);

    EXPECT_THROW(q.push(30), std::out_of_range);
}

TEST(QueueTest, ComplexType) {
    Queue<std::string> q(2);

    q.push("first");
    q.push("second");

    EXPECT_EQ(q.front(), "first");
    EXPECT_EQ(q.pop(), "first");
    EXPECT_EQ(q.pop(), "second");
}
