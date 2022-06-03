#include "sycl_device_code.hpp"

void foo()
{
  sycl::queue aq;
  std::vector<sycl::event> deps;
  const size_t BS = 128;
  aq.parallel_for(sycl::nd_range<1>{{BS}, {BS}}, deps, [=](sycl::nd_item<1> item) {
    int col = item.get_global_id(0);
  });
}
