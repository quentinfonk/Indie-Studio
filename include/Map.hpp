/*
** EPITECH PROJECT, 2021
** indie
** File description:
** map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <ctime>
#include <numeric>
#include <string_view>

class map 
{
    public:
        map();
        ~map();

        std::vector<std::vector<char>> create(int nb_player, int size);
        void create_map();
        void create_rooms();
        void create_L_room(int, int, int);
        void create_I_room(int, int, int);
        void take_largest_value();
        void create_real_map();
        void create_spawn();
        void create_empty_square();
        void create_high_square_part(int, int);
        void create_mid_square_part(int, int);
        void create_square_part(int, int);
        void create_down_square_part(int, int);
        std::vector<char> remove_spawn_point(std::vector<char>);
        void create_weapons();
    private:
        std::vector<std::vector<int>> plan_int;
        std::vector<std::vector<char>> plan_char;
        std::vector<int> vec_spawn;
        std::vector<int> vec_weapons;
        std::vector<char> char_list;
        std::vector<char> char_list_high;
        std::vector<char> char_list_down;
        std::vector<char> char_list_mid;
        int nb_player;
        int cut_high;
        int cut_down;
        int cut_left;
        int cut_right;
        int size;
};

std::vector<std::vector<char>> main_create_map(int, int);

#endif /* !MAP_HPP_ */
