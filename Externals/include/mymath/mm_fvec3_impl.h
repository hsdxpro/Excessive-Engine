#ifndef mm_fvec3_impl_h
#define mm_fvec3_impl_h

#include "mm_common.h"
#include "mm_fvec2_impl.h"

namespace mymath
{
  namespace impl
  {
    template<>
    class vec3i < float >
    {
    private:
      template< int at, int bt, int ct, int dt >
      class swizzle
      {
      private:
        __m128 v;
      public:
#ifndef MYMATH_FAST_COMPILE
        //For cases like swizzle = vec2i and swizzle = swizzle
        const vec3i& operator=( const vec3i& other )
        {
          v = _mm_shuffle_ps( other.d, other.d, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, ct, 0 ) );
          return *( vec3i* )this;
        }

        //For cases like swizzle *= vec2i and swizzle *= swizzle
        const vec3i& operator*=( const vec3i& other )
        {
          v = _mm_mul_ps( v, _mm_shuffle_ps( other.d, other.d, MM_SHUFFLE_SWIZZLE_HELPER(at, bt, ct, 0) ) );
          return *( vec3i* )this;
        }

        const vec3i& operator/=( const vec3i& other ); //needs notEqual, defined elsewhere

        const vec3i& operator+=( const vec3i& other )
        {
          v = _mm_add_ps( v, _mm_shuffle_ps( other.d, other.d, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, ct, 0 ) ) );
          return *( vec3i* )this;
        }

        const vec3i& operator-=( const vec3i& other )
        {
          v = _mm_sub_ps( v, _mm_shuffle_ps( other.d, other.d, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, ct, 0 ) ) );
          return *( vec3i* )this;
        }
#endif

        operator vec3i() const
        {
          return vec3i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, bt, ct, 0 ) ) );
        }
      };

      template<int at>
      class swizzle < at, at, at, -3 >
      {
      private:
        __m128 v;
      public:
        operator vec3i() const
        {
          return vec3i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, at, at, 0 ) ) );
        }
      };

      template<int at, int bt>
      class swizzle < bt, at, at, -3 >
      {
      private:
        __m128 v;
      public:
        operator vec3i() const
        {
          return vec3i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( bt, at, at, 0 ) ) );
        }
      };

      template<int at, int bt>
      class swizzle < at, bt, at, -3 >
      {
      private:
        __m128 v;
      public:
        operator vec3i() const
        {
          return vec3i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, bt, at, 0 ) ) );
        }
      };

      template<int at, int bt>
      class swizzle < at, at, bt, -3 >
      {
      private:
        __m128 v;
      public:
        operator vec3i() const
        {
          return vec3i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, at, bt, 0 ) ) );
        }
      };

      //vec2i swizzlers
      template<int at>
      class swizzle < at, at, -2, -3 >
      {
      private:
        __m128 v;
      public:
        operator vec2i<float>() const
        {
          return vec2i<float>( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, at, 0, 0 ) ) );
        }
      };


      template<int at, int bt>
      class swizzle < at, bt, -2, -3 >
      {
      private:
        __m128 v;
      public:
#ifndef MYMATH_FAST_COMPILE
        //For cases like swizzle = vec2i and swizzle = swizzle
        const vec2i<float>& operator=( const vec2i<float>& other )
        {
          //shuffle the other variable, and the rest of v (or 0 or 1) into one variable
          //so that we can shuffle them afterwards to the right place
          __m128 l = _mm_shuffle_ps( other.d, v, MYMATH_SHUFFLE( 0, 1, 3-at-bt, 3-at-bt ) );
          v = _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, 3 - at - bt, 0 ) );
          return *( vec2i<float>* )this;
        }

        //For cases like swizzle *= vec2i and swizzle *= swizzle
        const vec2i<float>& operator*=( const vec2i<float>& other )
        {
          __m128 l = _mm_shuffle_ps( other.d, impl::one, MYMATH_SHUFFLE( 0, 1, 3, 3 ) );
          v = _mm_mul_ps( v, _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, 3 - at - bt, 0 ) ) );
          return *( vec2i<float>* )this;
        }

        const vec2i<float>& operator/=( const vec2i<float>& other )
        {
          assert( !impl::is_eq( other.x, ( float )0 ) && !impl::is_eq( other.y, ( float )0 ) );
          __m128 l = _mm_shuffle_ps( other.d, impl::one, MYMATH_SHUFFLE( 0, 1, 3, 3 ) );
          v = _mm_div_ps( v, _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, 3 - at - bt, 0 ) ) );
          return *( vec2i<float>* )this;
        }

        const vec2i<float>& operator+=( const vec2i<float>& other )
        {
          __m128 l = _mm_shuffle_ps( other.d, impl::zero, MYMATH_SHUFFLE( 0, 1, 3, 3 ) );
          v = _mm_add_ps( v, _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, 3 - at - bt, 0 ) ) );
          return *( vec2i<float>* )this;
        }

        const vec2i<float>& operator-=( const vec2i<float>& other )
        {
          __m128 l = _mm_shuffle_ps( other.d, impl::zero, MYMATH_SHUFFLE( 0, 1, 3, 3 ) );
          v = _mm_sub_ps( v, _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, 3 - at - bt, 0 ) ) );
          return *( vec2i<float>* )this;
        }

#endif
        operator vec2i<float>() const
        {
          return vec2i<float>( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, bt, 0, 0 ) ) );
        }
      };

      //vec4 swizzlers for vec3
      template<int a>
      class swizzle < a, a, a, a >
      {
      private:
        __m128 v;
      public:
        operator vec4i<float>() const;
      };

      template<int a, int bt>
      class swizzle < bt, a, a, a >
      {
      private:
        __m128 v;
      public:
        operator vec4i<float>() const;
      };

      template<int a, int bt>
      class swizzle < a, bt, a, a >
      {
      private:
        __m128 v;
      public:
        operator vec4i<float>() const;
      };

      template<int a, int bt>
      class swizzle < a, a, bt, a >
      {
      private:
        __m128 v;
      public:
        operator vec4i<float>() const;
      };

      template<int a, int bt>
      class swizzle < a, a, a, bt >
      {
      private:
        __m128 v;
      public:
        operator vec4i<float>() const;
      };

      template<int a, int bt>
      class swizzle < bt, bt, a, a >
      {
      private:
        __m128 v;
      public:
        operator vec4i<float>() const;
      };

      template<int a, int bt>
      class swizzle < a, bt, bt, a >
      {
      private:
        __m128 v;
      public:
        operator vec4i<float>() const;
      };

      template<int a, int bt, int c>
      class swizzle < bt, c, a, a >
      {
      private:
        __m128 v;
      public:
        operator vec4i<float>() const;
      };

      template<int a, int bt, int c>
      class swizzle < a, a, bt, c >
      {
      private:
        __m128 v;
      public:
        operator vec4i<float>() const;
      };

      template<int a, int bt, int c>
      class swizzle < a, bt, c, a >
      {
      private:
        __m128 v;
      public:
        operator vec4i<float>() const;
      };

      template<int a, int bt, int c>
      class swizzle < bt, a, c, a >
      {
      private:
        __m128 v;
      public:
        operator vec4i<float>() const;
      };

      template<int a, int bt, int c>
      class swizzle < bt, a, a, c >
      {
      private:
        __m128 v;
      public:
        operator vec4i<float>() const;
      };

    protected:

    public:
#ifdef __GNUC__  //g++
#pragma GCC diagnostic ignored "-pedantic"
#endif
      union
      {
        struct
        {
          float x, y, z;
          float _dummy;
        };

        struct
        {
          float r, g, b;
          float _dummy2;
        };

        struct
        {
          float s, t, q;
          float _dummy3;
        };

#include "includes/vec3_swizzle_declarations.h"

        struct
        {
          float v[3];
          float _dummy4;
        };

        __m128 d;
      };
#ifdef __GNUC__  //g++
#pragma GCC diagnostic pop
#endif

      vec3i( const float& at, const float& bt, const float& ct ) : x( at ), y( bt ), z( ct )
      {
      }
      vec3i( const vec2i<float>& vec, const float& num )
      {
        *this = vec.xyy; z = num;
      }
      vec3i( const float& num, const vec2i<float>& vec )
      {
        *this = vec.xxy; x = num;
      }
#if MYMATH_STRICT_GLSL == 1
      explicit
#endif
        vec3i( const float& num )
      {
        d = _mm_set1_ps( num );
      }
      vec3i( const __m128& num ) : d( num )
      {
      }
      //vec3i() { d = impl::zero; }
      vec3i()
      {
      }
      vec3i( const vec3i<int>& v );
      vec3i( const vec3i<unsigned>& v );

      vec3i( std::initializer_list<float> list )
      {
        assert( list.size() == 3 );

        x = *( list.begin() + 0 );
        y = *( list.begin() + 1 );
        z = *( list.begin() + 2 );
      }

      MM_OVERRIDE_NEW

      float& operator[]( const unsigned int& num )
      {
        assert( num < 3 && this );
        return v[num];
      }

      const float& operator[]( const unsigned int& num ) const
      {
        assert( num < 3 && this );
        return v[num];
      }

      const vec3i& operator*= ( const vec3i& vec )
      {
        d = _mm_mul_ps( d, vec.d );
        return *this;
      }

      const vec3i& operator/= ( const vec3i& vec ); //needs notEqual defined elsewhere

      const vec3i& operator+= ( const vec3i& vec )
      {
        d = _mm_add_ps( d, vec.d );
        return *this;
      }

      const vec3i& operator-= ( const vec3i& vec )
      {
        d = _mm_sub_ps( d, vec.d );
        return *this;
      }

      const vec3i operator++ ( ) //pre
      {
        d = _mm_add_ps( d, impl::one );
        return *this;
      }

      const vec3i operator++ ( impl::post )
      {
        vec3i tmp = *this;
        ++( *this );
        return tmp;
      }

      const vec3i operator-- ( ) //pre
      {
        d = _mm_sub_ps( d, impl::one );
        return *this;
      }

      const vec3i operator-- ( impl::post )
      {
        vec3i tmp = *this;
        --( *this );
        return tmp;
      }

      const unsigned int length() const
      {
        return 3;
      }
    };
  }
}

#endif
