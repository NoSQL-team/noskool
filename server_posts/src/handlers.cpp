//
// Created by steve on 15.12.2020.
//

#include "../include/handlers.h"
#include "../include/utility_for_lib.h"


std::string Handlers::for_user(const std::string& id_request, const std::map<std::string, size_t>& args) {
    std::string usr_id = std::to_string(args.at("user_id"));
    std::string sql_limit = std::to_string(args.at("limit"));
    std::string sql_offset = std::to_string(args.at("offset"));

    std::vector<std::string> friends = get_friends_id(usr_id);

    if (!friends.empty()) {
        // преобразуем вектор к строке с запятыми чтобы использовать в IN SQL
        std::ostringstream oss;
        std::copy(friends.begin(), friends.end() - 1,
                std::ostream_iterator<std::string>(oss, ","));
        oss << friends.back(); // копируем последний символ, чтобы не было пробела в конце
        std::string need_posts = oss.str();

        std::vector<Post> vec_posts = _db.get_posts_for_user(need_posts, sql_limit, sql_offset);
        std::string posts = vec_posts_to_json(vec_posts);
        return id_request + "\n\n" + posts;
    } else {
        return id_request + "\n\n" + "{\"data\": []}";
    }


}


std::string Handlers::all_posts(const std::string& id_request, const std::map<std::string, size_t>& args) {
    std::string sql_limit = std::to_string(args.at("limit"));
    std::string sql_offset = std::to_string(args.at("offset"));

    std::vector<Post> vec_posts = _db.get_all_posts(sql_limit, sql_offset);
    std::string posts = vec_posts_to_json(vec_posts);
    return id_request + "\n\n" + posts;
}


std::string Handlers::popular_posts(const std::string& id_request, const std::map<std::string, size_t>& args) {
    std::string sql_limit = std::to_string(args.at("limit"));
    std::string sql_offset = std::to_string(args.at("offset"));

    std::vector<Post> vec_posts = _db.get_popular_posts(sql_limit, sql_offset);
    std::string posts = vec_posts_to_json(vec_posts);
    return id_request + "\n\n" + posts;
}


std::string Handlers::user_posts(std::string const& id_request, std::map<std::string, size_t> const& args) {
    std::string usr_id = std::to_string(args.at("user_id"));
    std::string sql_limit = std::to_string(args.at("limit"));
    std::string sql_offset = std::to_string(args.at("offset"));

    std::vector<Post> vec_posts = _db.get_user_posts(usr_id, sql_limit, sql_offset);
    std::string posts = vec_posts_to_json(vec_posts);

    return id_request + "\n\n" + posts;
}


std::string Handlers::one_post(std::string const& id_request, std::map<std::string, size_t> const& args) {
    std::string post_id = std::to_string(args.at("post_id"));
    if (_db.post_exist(post_id)) {
        Post one = _db.get_one_post(post_id);
        return id_request + "\n\n" + post_to_json(one);
    } else {
        return id_request + "\n\n" + "{\"response\": \"error\"}";
    }
}


std::string Handlers::delete_post(std::string const& id_request, std::map<std::string, size_t> const& args) {
    std::string post_id = std::to_string(args.at("post_id"));
    std::string user_id = std::to_string(args.at("user_id"));

    std::string status = _db.delete_post(post_id, user_id);
    return id_request + "\n\n" + "{\"response\": \"" + status + "\"}";

}


std::string Handlers::create_post(
                                    const std::string& id_request,
                                    const std::map<std::string, size_t>& args,
                                    std::string& body) {

    try {
        Post new_post = parse_body(body);
        std::string new_post_id  = _db.create_post(new_post);
        return id_request + "\n\n" + "{\"response\": \"created, new post id: " + new_post_id + "\"}";
    } catch(std::exception const& e) {
        return id_request + "\n\n" + "{\"response\": \"error\"}";
    }
}


std::string Handlers::add_like(const std::string &id_request, const std::map<std::string, size_t> &args) {
    std::string post_id = std::to_string(args.at("post_id"));
    std::string user_id = std::to_string(args.at("user_id"));
    std::string status = _db.add_like_by_id(post_id, user_id);
    return id_request + "\n\n" + "{\"response\": \"" + status + "\"}";
}


std::string Handlers::del_like(const std::string &id_request, const std::map<std::string, size_t> &args) {
    std::string post_id = std::to_string(args.at("post_id"));
    std::string user_id = std::to_string(args.at("user_id"));
    std::string status = _db.del_like_by_id(post_id, user_id);
    return id_request + "\n\n" + "{\"response\": \"" + status + "\"}";
}

