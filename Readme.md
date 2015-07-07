Disco is a network peer discovery library written in C and released into the
public domain for maximum portability.

TODO
---
* Add receive_message() broadcast listener function
* Add timeout_milliseconds parameter to create_broadcast_socket()
* Levelize
  * network.h - socket handling (options, creation, address handling, port conversion, etc.)
  * broadcast.h - broadcast - multicast on IPv6 - handling (broadcast socket creation/destruction, messaging, etc.)
  * disco.h - discovery API (handshake, versioning, etc.)
* broadcaster.c - change to use INADDR_BROADCAST (rather than 255.255.255.255)
* Support multicast on IPv6
* Make C versions work on Windows
* Make C versions work on Linux
* Encapsulate discovery into a library ('Disco') - prefix functions with dsc_

* Work out discovery API
```
    peer_locator_t {
        int (*get_peers)(dsc_peers_t* peers) // Pointer to function for returning peers
    }

    peers_t {
    }

    peer_t {
        char* id,
        address ip_address
    }

    // Q: This implies that memory (or other resource) allocation happens in this function
    //    (if required). Should we not also have a 'destroy' function?
    // Q: Should we not have a 'destroy' function for everything?
    // Q: Would creating, passing round and destroying a 'context' be the easiest way to handle this?
    // Q: Or having 'startup'/'cleanup' functions (which is similar to the above but without the need
    //    for passing around context (essentially there is a hidden global somewhere - a static returned from
    //    a local (static) function)?
    // Q: Startup could be called implicitly by all other functions. Would this be useful, or confusing?
    // Q: Could we hide 'cleanup' too (at_exit function)?
    // Q: Might it be safer just to support 'cleanup' from being passed to 'atexit' in a client program?

    // Q: Should we disallow any dynamic memory handling from within the library?
    // Q: Or, perhaps, allow setting custom memory handling routines?
    dsc_peer_locator_t* peer_locator = dsc_local_peer_locator();

    dsc_peers_t peers;
    if (peer_locator->get_peers(&peers) == DSC_ERROR) {
        fprintf(stderr, "Failed to get peers\n");
        exit(1);
    }

    // This does not encapsulate peers_t at all -> it is clearly a linked list
    for (peer_t* peer = peers->first; peer != NULL; peer = peer->next) {
        // ...
    }

    // This encapsulates peers_t but requires keeping track of indices outside
    for (int i = 0; i < peers->count(); i++) {
        peer_t* peer = peers->get(i);
    }

    // Q: What do we want to do with the list of peers?
    // A: Send them a heartbeat? Q: Who decides the list of peers to send to...? Is it 'opt-in' for the
    // senders or the receivers...?
    // This encapsulates performing the same function with all peers.
    // Q: How does the passed function send back results?
    // A: Via passed 'context' pointer
    peers->do(/* some function */, void* context);

    // Q: Does this make sense to check the list of peers via a heartbeat?
    peers = peers->send_heartbeat();
    // A: Probably not, since it takes some time to determine that a non-responsive peer should be removed
    // Q: What about:
    dsc_heartbeat_t heartbeat;
    peers->send_ping(&heartbeat);
    // some time later...
    peers->receive_pong(&heartbeat);
    // Q: Doesn't it make sense to allow the use of 'select' to wait for responses?
    // Q: Doesn't the above API allow this?
    // A: Yes, I think so. send_pong() would create the TCP sockets and add them to the fd_set.
    //    'select' would then be called on the fd_set in receive_pong()
    // Q: So where is fd_set stored?
    // A: Within the heartbeat_t
    // Q: Won't this cause a ping from A->B, a pong from B->A and also a ping from B->A and a pong from A->B?
    // A: Yes
    // Q: Should we prevent this?
    // Q: If not, do we need ping+pong or should we just have heartbeat A->B and heartbeat B->A?
    // Q: If so, can we make do with heartbeat == discover?
    // Q: If so, does this work for non-local heartbeats (i.e. those which cannot be discovered automatically
    //    using UDP broadcast)?
    // A: Yes, if heartbeat is point-to-point in that case.
    // Q: Should all heartbeats be point-to-point?
    // Q: And if so, can heartbeats be UDP (non-broadcast)?

    // Discovery:
    //     A broadcasts 'HERE' + A_address
    //     B receives 'HERE' + A_address
    //     B responds to A 'ICU' + B_address
    //     C receives 'HERE' + A_address
    //     C responds to A 'ICU' + C_address
    // Heartbeat
    //     A sends 'ALIVE' to B_address
    //     A sends 'ALIVE' to C_address
    // NB: Every node just broadcasting 'HERE' + address could work for discovery and heartbeat ON LOCAL NETWORK
```
