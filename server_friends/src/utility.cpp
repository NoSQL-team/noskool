//
// Created by Andrew Kireev on 11.11.2020.
//

#include "utilty.h"

#include <map>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

static const std::map<std::string, tcp_network::RequestDestination> servers_adrs_ =
		{{"5", tcp_network::RequestDestination::POST_SERV},
		 {"4", tcp_network::RequestDestination::FRIEND_SERV},
		 {"3", tcp_network::RequestDestination::HTTP_SERV},
		 {"2", tcp_network::RequestDestination::USER_SERV},
		 {"1", tcp_network::RequestDestination::AUTH_SERV}
		};


namespace tcp_network {

	RequestDestination ParseJson::get_destination(std::string& request) {
		std::string destination = request.substr(0, request.find('\n'));
//        std::cout << destination << std::endl;
		if (servers_adrs_.count(destination) == 0) {
			return RequestDestination::UNKNOWN;
		}
		return servers_adrs_.at(destination);
	}

	std::map<std::string, std::string> ParseJson::parse(std::string& request) {
		std::map<std::string, std::string> requsts;

		auto iter = request.find('\n');
		requsts.insert({"number", request.substr(0, iter)});
		request.erase(0, iter + 1);
		iter = request.find('\n');
		std::string buffer = request.substr(0, iter);
		buffer = request.substr(13, iter);
		auto bufIter = buffer.find('/');
		buffer = buffer.substr(0, bufIter);
		requsts.insert({"type", buffer});
		request.erase(0, iter + 1);
		iter = request.find('\n');
		requsts.insert({"auth", request.substr(0, iter)});
		request.erase(0, iter + 2);

		if(!request.empty()) {
			std::stringstream ss(request);
			boost::property_tree::ptree pt;
			boost::property_tree::read_json(ss, pt);
			using boost::property_tree::ptree;
			ptree::const_iterator end = pt.end();


			for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
				requsts.insert({std::string(it->first), it->second.get_value<std::string>()});
			}
		}
		return requsts;
	}

	void print_destination(RequestDestination destination) {
		if (destination == RequestDestination::POST_SERV)
			std::cout << "POST_SERV" << std::endl;
		else if (destination == RequestDestination::AUTH_SERV)
			std::cout << "AUTH_SERV" << std::endl;
		else if (destination == RequestDestination::FRIEND_SERV)
			std::cout << "FRIEND_SERV" << std::endl;
		else if (destination == RequestDestination::USER_SERV)
			std::cout << "USER_SERV" << std::endl;
	}

}