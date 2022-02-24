#include <gtest/gtest.h>
#include "../tools/ImageBuffer.h"


/**
 * Test of initial state of the buffer
 */
TEST(ImageBufferTest, InitialConditions) {
    ImageBuffer<int, 4> buffer;

    EXPECT_EQ(buffer.getSize(), 4);
    EXPECT_EQ(buffer.getFree(), 4);
}



TEST(ImageBufferTest, SimplePushFetch) {
    ImageBuffer<int, 4> buffer;

    buffer.pushOverride(1);
    EXPECT_EQ(buffer.getLastIndex(), 0);
    buffer.pushOverride(2);
    buffer.pushOverride(3);
    buffer.pushOverride(4);
    buffer.pushOverride(5);

    EXPECT_EQ(buffer.getLastIndex(), 0);
    EXPECT_EQ(buffer.fetchLast(), 5);

    buffer.pushOverride(6);
    EXPECT_EQ(buffer.getLastIndex(), 1);
    EXPECT_EQ(buffer.fetchLast(), 6);
}

TEST(ImageBufferTest, IndexIncrementing) {
    ImageBuffer<int, 4> buffer;
    EXPECT_EQ(buffer.getLastIndex(),-1);
    EXPECT_EQ(buffer.getCurrentIndex(),-1);

    buffer.pushOverride(1);
    EXPECT_EQ(buffer.getLastIndex(),0);
    EXPECT_EQ(buffer.getCurrentIndex(),0);
    buffer.pushOverride(1);
    EXPECT_EQ(buffer.getLastIndex(),1);
    EXPECT_EQ(buffer.getCurrentIndex(),0);
    buffer.pushOverride(1);
    buffer.pushOverride(1);
    buffer.pushOverride(1);
    EXPECT_EQ(buffer.getLastIndex(),0);
    EXPECT_EQ(buffer.getCurrentIndex(),1);
    buffer.pushOverride(1);
    buffer.pushOverride(1);
    buffer.pushOverride(1);
    EXPECT_EQ(buffer.getLastIndex(),3);
    EXPECT_EQ(buffer.getCurrentIndex(),0);
}

TEST(ImageBufferTest, ComplexPushFetch){
    ImageBuffer<int, 4> buffer;

    bool tmp = true;
    buffer.fetchCurrent(tmp);
    EXPECT_EQ(tmp, false);
    buffer.pushOverride(1);
    buffer.pushOverride(2);
    buffer.pushOverride(3);
    buffer.pushOverride(4);
    EXPECT_EQ(buffer.fetchCurrent(tmp),1);
    EXPECT_EQ(tmp, true);
    EXPECT_EQ(buffer.fetchCurrent(tmp),2);
    EXPECT_EQ(tmp, true);
    EXPECT_EQ(buffer.fetchCurrent(tmp),3);
    EXPECT_EQ(tmp, true);
    EXPECT_EQ(buffer.fetchCurrent(tmp),4);
    EXPECT_EQ(tmp, true);
    EXPECT_EQ(buffer.fetchCurrent(tmp),0);
    EXPECT_EQ(tmp, false);
}