#include <null-mono.h>

namespace mono {
	thread_t* thread_t::attach() {
		return mono.thread_attach(domain_t::root());
	}

	void thread_t::detach() {
		mono.thread_detach(this);
	}
}