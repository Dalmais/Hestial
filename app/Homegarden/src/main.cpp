// Copyright (c) 2023 Romain Damais <dalmais<at>gmail.com>
// See end of file for extended copyright information

#include <iostream>
#include <gtest/gtest.h>

int main(int argc,  char** argv){
    std::cout << "Hello World!" << std::endl;
    return 0;
}

TEST(TestTopic,TrivialEquality) {
    EXPECT_EQ(main(), 0);
}




/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
