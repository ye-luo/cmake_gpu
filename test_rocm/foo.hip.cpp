#include <hipblas.h>
void foo()
{
  hipblasStatus_t status;
  hipblasHandle_t handle;
  status = hipblasCreate(&handle);
  status = hipblasDestroy(&handle);
}
