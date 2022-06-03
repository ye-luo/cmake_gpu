#include "sycl_device_code.hpp"

void boo()
{
  #pragma omp parallel
  foo();
}
