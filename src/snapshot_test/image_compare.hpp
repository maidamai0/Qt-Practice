#pragma once

#include <QColor>
#include <QFile>
#include <QImage>

#include <iostream>
#include <string>

/**
 * @brief compare two image
 *
 * @param expected    the expected image path
 * @param actrual     the actual image path
 * @param theshold    theshold to decide if these iamges are the same
 * @return true       the two image are considered the same
 * @return false      the two imag are considered different
 */
auto image_diff(const std::string& expected, const std::string& actual,
                const double theshold = 0.1) -> bool {
  auto check_file_exist = [](const std::string& path) {
    if (!QFile(path.c_str()).exists()) {
      std::cout << "File " << path << " not exist\n";
      return false;
    }

    return true;
  };

  if (!check_file_exist(expected) || !check_file_exist(actual)) {
    return false;
  }

  QImage expected_image(expected.c_str());
  QImage actual_image(actual.c_str());

  int height_expected = expected_image.height();
  int width_expected = expected_image.width();
  int height_actual = actual_image.height();
  int width_actual = actual_image.width();
  if (width_expected != width_actual || height_expected != height_actual) {
    std::cerr << "Error, pictures must have identical dimensions!\n";
    return false;
  }

  double total_diff = 0.0; // holds the number of different pixels
  for (int y = 0; y < height_expected; y++) {
    uint* first_line = (uint*) expected_image.scanLine(y);
    uint* second_line = (uint*) actual_image.scanLine(y);
    for (int x = 0; x < width_expected; x++) {
      uint pixel_first = first_line[x];
      int r_first = qRed(pixel_first);
      int g_first = qGreen(pixel_first);
      int b_first = qBlue(pixel_first);
      uint pixel_second = second_line[x];
      int r_second = qRed(pixel_second);
      int g_second = qGreen(pixel_second);
      int b_second = qBlue(pixel_second);

      const static auto max_color = 255.0;
      total_diff += std::abs(r_first - r_second) / max_color;
      total_diff += std::abs(g_first - g_second) / max_color;
      total_diff += std::abs(b_first - b_second) / max_color;
    }
  }

  const auto diff = (total_diff * 100) / (width_expected * height_expected * 3);

  return (diff < theshold);
}