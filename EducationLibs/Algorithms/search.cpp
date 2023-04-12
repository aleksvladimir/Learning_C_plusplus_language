
#include <vector>

constexpr auto NOT_FOUND = -1;

/**
 * \brief Бинарный поиск
 * \param arr - массив для поиска
 * \param valueSearching - значение для поиска в массиве
 * \param operationSearchCount - затраченное количество операций на поиск
 * \return в случае успеха - индекс найденного элемента, иначе - NOT_FOUND
 */
int binary_search(const std::vector<int> & arr, const int valueSearching, int& operationSearchCount)
{
  int leftIdx = 0;
  int rightIdx = arr.size() - 1;

  while ( leftIdx <= rightIdx )
  {
    // деление суммы индексов крайних точек диапазона поиска на 2 дает индекс середины выбранного диапазона в границах массива
    const auto middleIdx = (leftIdx + rightIdx) / 2;
    if (valueSearching == arr[ middleIdx ])
    {
      operationSearchCount++;
      return middleIdx;
    }
    
    if (valueSearching < arr[middleIdx])
      rightIdx = middleIdx - 1; // т.к. значение из middleIdx уже проверено - пропускаем
    else
      leftIdx = middleIdx + 1;  // т.к. значение из middleIdx уже проверено - пропускаем

    operationSearchCount++;
  }
  return NOT_FOUND;
}
