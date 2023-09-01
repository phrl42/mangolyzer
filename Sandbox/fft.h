#ifndef __FFT_H_
#define __FFT_H_

#include <cmath>
#include <complex>
#include <iomanip>
using namespace std::complex_literals;

inline float amp(std::complex<float> v)
{
  float s = fabsf(v.imag());
  float c = fabsf(v.real());

  if(s < c) return c;
  return s;
}

inline void fft(float in[], size_t stride, std::complex<float> out[], size_t n)
{
  float pi = atan2f(1, 1) * 4;
  // fft

  if(!n)
    return;
  
  if(n == 1)
  {
    out[0] = in[0];
  }

  fft(in, stride*2, out, n/2);
  fft(in + stride, stride * 2, out + n/2, n/2);

  for(size_t k = 0; k < n/2; ++k)
  {
    float t = (float)k/n;
    std::complex<float> v = std::exp((float)(-2 * pi * t) * std::complex<float>(1i) ) * out[k + n/2];
    std::complex<float> e = out[k];
    out[k] = e + v;
    out[k + n/2] = e -v;
  }
}

inline void dft(float in[], std::complex<float> out[], size_t n)
{
  float pi = atan2f(1, 1) * 4;

  for(size_t f = 0; f < n; f++)
  {
    out[f] = 0;
    for(size_t i = 0; i < n; i++)
    {
      float t = (float)i/n;
      out[f] += in[i] * std::exp((std::complex<float>)1i * pi * 2.0f * t * (float)f);
    }
  }
}
/*void dft(float *in, float complex *out, size_t n)
{
  float pi = atan2f(1, 1) * 4;
  // dft
  for(size_t f = 0; f < n; f++)
  {
    out[f] = 0;
    for(size_t i = 0; i < n; i++)
    {
      float t = (float)i / n;
      out[f] += in[i]*cexp(I* 2*pi* f*t);
    }
  }
}*/

#endif
