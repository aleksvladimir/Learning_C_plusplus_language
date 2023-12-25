#pragma once
#include <vector>

namespace task_88
{
  class Solution {
  public:
    void merge( std::vector<int> & nums1, short m, const std::vector<int> & nums2, short n )
    {
      short i = m - 1, j = n - 1, k = m + n - 1;
      while ( i >= 0 && j >= 0 )
        nums1[ k-- ] = nums1[ i ] > nums2[ j ] ? nums1[ i-- ] : nums2[ j-- ];
      while ( j >= 0 )
        nums1[ k-- ] = nums2[ j-- ];
    }
  };
}
