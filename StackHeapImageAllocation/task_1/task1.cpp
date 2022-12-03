#include <bitset>
#include <cstddef>
#include <iostream>
#include <vector>
int main() {

  std::vector<double> data(81*102400/8);

  while (true) {
    for (int i = 0; i < 102400/8; ++i) {
      data.emplace_back(1.2);
    }
    std::cout << sizeof(std::vector<double>) + (sizeof(int) * data.size()) / 1024 << std::endl;
    if (data.size() / 1024. - 7700. > 0) {
      std::cout << data.size()*8 / 1024 << "[KiB]"
                << " "
                << "Allocated in the stack" << std::endl;
      if (data.size() / 1024. - 8100. > 0) {
        std::cerr << std::endl;
      }
    }
  }

  return 0;
}