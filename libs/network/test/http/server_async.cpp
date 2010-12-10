
// Copyright 2010 Dean Michael Berris. 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE HTTP Asynchronous Server Tests

#include <boost/config/warning_disable.hpp>
#include <boost/network/include/http/server.hpp>
#include <boost/network/utils/thread_pool.hpp>

namespace http = boost::network::http;
namespace utils = boost::network::utils;

struct async_hello_world;
typedef http::async_server<async_hello_world> server;

struct async_hello_world {
    void operator()(server::request const & request, server::connection_ptr connection) {
        static server::response_header headers[] = {
            {"Connection", "close"}
            , {"Content-Type", "text/plain"}
            , {"Server", "cpp-netlib/0.8-devel"}
        };
        if (request.method == "HEAD") {
            connection->set_status(server::connection::ok);
            connection->set_headers(boost::make_iterator_range(headers, headers+3));
        } else if (request.method == "GET") {
            static char const lorem_ipsum_10k[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse non eros nisl. Proin in risus quam, non pellentesque est. Suspendisse vehicula condimentum odio, id suscipit libero vehicula id. Mauris quis cursus tellus. Sed interdum pretium rutrum. Etiam sagittis dolor sit amet lacus fermentum volutpat. Sed fermentum accumsan ante id aliquet. Morbi cursus imperdiet eros, vitae molestie nibh luctus quis. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec quis nulla elit, vitae consequat felis. Mauris in blandit nibh. Aenean ac ultricies magna. Quisque aliquet tellus vitae ipsum egestas vitae semper turpis consectetur. Mauris vitae mauris id mi pulvinar ullamcorper. Cras iaculis, orci tempor aliquet malesuada, lacus enim consequat augue, ut consectetur orci mauris nec justo. Nulla metus libero, tempor et lobortis quis, cursus eu sapien. Morbi volutpat odio sed elit tincidunt sed imperdiet sem sagittis.Donec sapien enim, pharetra vehicula blandit ac, faucibus eu ipsum. Integer vehicula dolor nisi. Nunc quis quam eget lectus feugiat interdum id at quam. Donec hendrerit neque a lorem elementum elementum. Ut non ornare neque. Nulla venenatis tempus leo lobortis condimentum. Fusce eros magna, pellentesque non mollis interdum, porttitor a tellus. Suspendisse at erat non lorem aliquam aliquet ornare id felis. Praesent tincidunt, lectus nec dignissim pharetra, ipsum elit sodales massa, eget accumsan eros purus at metus. Sed sodales dolor vitae magna blandit eget bibendum sapien consectetur. Mauris a viverra felis. Donec sodales tempor lorem, vitae mollis tellus scelerisque quis. Praesent ullamcorper auctor sapien sit amet condimentum. In hac habitasse platea dictumst. In nec laoreet nisi.Nulla facilisi. Nunc varius lectus in nisl condimentum ut bibendum turpis dapibus. Nam a lacus sem. Integer ultricies varius eros, viverra scelerisque diam semper non. In risus est, mattis sed condimentum at, scelerisque at urna. Sed nunc lorem, convallis quis accumsan et, aliquam eu mauris. Nulla fringilla orci metus. Etiam ut purus metus, sed placerat lacus. Morbi porta mauris eget nunc vehicula consectetur. In scelerisque pharetra lacinia. Curabitur ultrices vestibulum ante eget consectetur. Donec nec augue sapien. Donec at feugiat risus. Nulla sit amet justo ac tortor ullamcorper pharetra at sit amet enim. Suspendisse ac massa metus. Quisque pretium, nunc eu vehicula lobortis, lorem ante posuere nisl, sit amet iaculis felis odio quis massa. Duis nec lorem urna, ac porttitor mauris. Nunc blandit, massa vel tincidunt interdum, turpis libero tincidunt eros, sit amet posuere nisi ipsum a nunc. In porta adipiscing sodales. Etiam blandit, nisl eget ultrices laoreet, mauris massa commodo leo, in interdum metus elit vel velit. Quisque sodales lectus eu ligula auctor at scelerisque lectus commodo. Sed luctus nunc vel dui pretium posuere. Donec a ullamcorper odio. Integer eget nunc leo. Nulla facilisi. Vestibulum bibendum, sem quis porttitor lobortis, felis diam convallis diam, id malesuada lorem mi ut libero. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Praesent cursus metus sit amet neque gravida eu ullamcorper mi fermentum. Sed ut erat ac sem facilisis blandit sit amet eget odio. Morbi a tortor lectus. Phasellus et erat vel tellus pharetra luctus. Nulla molestie sollicitudin sapien vitae commodo. Sed molestie fringilla velit eget varius. Nam augue augue, ultrices eget viverra quis, mattis a mi. Morbi varius sagittis tempor. Praesent a cursus elit. Etiam non molestie enim. Nullam eleifend, sapien ac varius suscipit, lectus orci bibendum nisl, eu pretium lectus dolor at nisl. Etiam posuere viverra condimentum. Etiam nulla urna, consequat eget laoreet vel, tempus nec lorem. Donec ut risus quam. Praesent vitae felis justo. Suspendisse eget magna sed leo suscipit semper. Suspendisse eget mauris lacus, sit amet viverra mauris. Cras sed ligula a tellus faucibus tincidunt. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi dictum nisi eget dolor faucibus eu scelerisque ipsum posuere. Aenean varius ultricies est, non tristique lectus auctor a. Curabitur a augue non ligula mollis gravida. Aliquam erat volutpat. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Nam pellentesque vehicula augue, quis posuere nunc dapibus a. Phasellus urna purus, dapibus ultricies iaculis a, laoreet nec sem. Nulla gravida purus eget urna elementum faucibus. Etiam magna neque, iaculis eget egestas et, consequat rutrum urna. Quisque euismod tempus enim, id pulvinar orci cursus a. Vestibulum in urna sapien, nec tempor ligula. Quisque viverra sapien eget justo elementum nec egestas erat placerat. Sed elementum mauris vel felis mattis id adipiscing tellus commodo. Quisque sapien odio, pharetra non accumsan ac, aliquam nec tortor. Sed vitae aliquam magna. Curabitur quam leo, eleifend id bibendum sit amet, viverra et elit. Duis elementum nulla quis nulla rhoncus consectetur. Cras id ante faucibus est viverra facilisis. Fusce vitae odio tortor. Etiam vitae est nunc, et molestie metus. Proin pellentesque, metus sed luctus venenatis, magna metus facilisis lectus, quis bibendum libero turpis eu arcu. Nunc dapibus nibh id eros ultrices vehicula. Vestibulum porta mauris et est vulputate vitae euismod sem ullamcorper. Pellentesque id accumsan sapien. Curabitur sodales viverra arcu ac facilisis. Sed congue facilisis sapien a tempus. Pellentesque elementum, metus sit amet rutrum volutpat, massa enim rutrum purus, ac rhoncus velit erat ac leo. Duis ornare sem vulputate ligula cursus volutpat. Aenean posuere accumsan elit non vestibulum. Duis nunc ligula, vulputate nec iaculis vitae, fermentum vel ante. Sed eget purus ipsum. Cras condimentum mattis hendrerit. Mauris congue arcu sed ante bibendum eget mattis odio feugiat. Donec felis turpis, dignissim mattis varius non, auctor a risus. Pellentesque elit mi, molestie et posuere non, volutpat adipiscing libero. Curabitur in interdum neque. Maecenas luctus pulvinar est, posuere pharetra magna placerat non. Fusce mollis elementum est ac venenatis. Nam quis metus id libero euismod faucibus eget ut tortor. Integer est nibh, hendrerit eget hendrerit in, pretium ac purus. Suspendisse sagittis, erat a placerat malesuada, risus sem condimentum magna, non congue nisi tellus at massa. Aliquam mattis erat id lorem tincidunt sagittis. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin scelerisque tempus blandit. Cras dignissim, nibh elementum tempor tempor, nisi odio iaculis lectus, eget suscipit dui lacus eu nunc. Aliquam quis sem turpis, quis condimentum nunc. Nunc ac justo leo, ut tempus elit. Cras in tempus ante. Suspendisse porttitor libero sit amet felis hendrerit ullamcorper. Ut tellus nunc, fermentum in tristique et, malesuada eget arcu. Nam mi massa, vehicula id fermentum vitae, vehicula quis diam. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nulla arcu lorem, ultrices ac ullamcorper id, aliquet vitae eros. Quisque ut arcu augue, eu faucibus leo. Ut mollis interdum felis vitae aliquam. Mauris metus nisi, dictum quis ornare ac, pellentesque in magna. Mauris tincidunt, justo vitae sollicitudin vehicula, sem arcu ullamcorper nunc, vitae tincidunt tellus massa nec diam. Duis pharetra venenatis convallis. Maecenas vulputate, orci eget adipiscing venenatis, nunc turpis congue odio, et lacinia nisi dolor varius lectus. Pellentesque vehicula, nulla in ultricies ullamcorper, magna enim lobortis velit, sed ornare arcu eros quis dui. Donec laoreet sem imperdiet ligula blandit sagittis. Suspendisse nisl felis, ultrices eget tristique quis, feugiat quis nisi. Curabitur iaculis blandit dui, vitae euismod lectus commodo vitae. Nam at tortor non ipsum commodo consequat. Donec tristique tellus id sem dignissim non pharetra nibh tristique. Duis a massa viverra odio ornare rhoncus. Curabitur et quam nisi, sagittis convallis odio. Vivamus justo justo, laoreet nec pellentesque vitae, porta non lorem. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Aenean ac nulla id turpis pharetra luctus in convallis magna. Curabitur id dolor ac tortor congue convallis varius eget lectus. Duis ultricies, tortor tincidunt porttitor condimentum, dui felis viverra magna, nec egestas libero lorem nec tellus. Integer viverra mauris id elit egestas rutrum et at turpis. Praesent pellentesque dignissim accumsan. Suspendisse cursus tempor ipsum, ut tempor lorem vehicula sit amet. Fusce feugiat blandit mauris sit amet dictum. Integer tempor vestibulum turpis, at rhoncus lectus sollicitudin et. Morbi nec sollicitudin sem. Nulla nisl nisl, fringilla in sollicitudin eu, lobortis ut nunc. Quisque euismod felis enim, at blandit velit. In tristique mollis quam, in faucibus mi hendrerit non. Phasellus laoreet posuere nunc sit amet congue. Nam laoreet, sapien eget lacinia lacinia, turpis erat tristique magna, id pellentesque turpis odio non augue. Donec tristique pharetra arcu, sed faucibus lorem tempus ac. Nulla facilisi. Aliquam sagittis, est eget dignissim pretium, massa lacus pulvinar diam, id pretium nibh urna quis tellus. Ut tristique volutpat libero id porta. Vivamus congue nisi vel nisi sagittis ut facilisis lorem facilisis. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Praesent et nunc et ligula interdum mattis. Sed bibendum cursus nisl, ut tempus magna placerat vel. Sed porttitor lobortis tristique. Ut mauris orci, aliquet in pharetra et, volutpat vel metus. Quisque tincidunt, nisi at tempus consequat, lorem ligula consequat purus, vel ullamcorper lacus ligula in diam. Nulla a semper dolor. Integer porttitor lectus dolor, eget imperdiet tortor. Integer vitae feugiat nibh. Quisque nisi arcu, auctor pellentesque luctus dapibus, euismod vitae ligula. Aliquam quis purus sit amet orci porta auctor eu at mauris. Quisque ac justo nisl viverra fusce.";
            connection->set_status(server::connection::ok);
            connection->set_headers(boost::make_iterator_range(headers, headers+3));
            connection->write(lorem_ipsum_10k);
        } else {
            connection->set_status(server::connection::not_supported);
            connection->set_headers(boost::make_iterator_range(headers, headers+3));
            connection->write("Unsupported method.");
        }
    }
};

int main(int argc, char * argv[]) {
    utils::thread_pool thread_pool(2); 
    async_hello_world handler;
    server instance("127.0.0.1", "8000", handler, thread_pool, http::_reuse_address=true);
    instance.run();
    return 0;
}

