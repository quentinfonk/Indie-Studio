/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Message
*/

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <string>

static const int MSG_MAX_LEN = 1024;

static const std::string INCOMMING_CONNECTION = "##100##"; // New connection from a client
static const std::string ACCEPTED_CONNECTION = "##201##"; // New connection is accepted
static const std::string TIMEOUT_CONNECTION = "##408##"; // Connection timeout
static const std::string CLOSING_SERVER = "##500##"; // Server is closing (host disconnected)
static const std::string CLOSING_CONNECTION = "##501##"; // Server is closing this code is sent to all client
static const std::string CLIENT_CLOSING_CONNECTION = "#502#"; // A client (non-host) disconnected from the server (Escape or CTRL-C)

#endif /* !MESSAGE_HPP_ */
