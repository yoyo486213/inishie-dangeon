#ifndef IMAGEGENERATOR_HPP
#define IMAGEGENERATOR_HPP

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

class ImageGenerator
{
public:

    static std::string resolvePath(char c) {
        if (c >= 'a' && c <= 'z') {
            return RESOURCE_DIR"/Text/SmallLetter/" + std::string(1, c) + ".png";
        } else if (c >= 'A' && c <= 'Z') {
            return RESOURCE_DIR"/Text/BigLetter/" + std::string(1, c) + ".png";
        } else if (c >= '0' && c <= '9') {
            return RESOURCE_DIR"/Text/Number/" + std::string(1, c) + ".png";
        } else {
            std::cerr << "Unsupported character: " << c << std::endl;
            return "";
        }
    }

    static unsigned char* loadImage(const std::string& filename, int& width, int& height, int& channels) {
        unsigned char* img = stbi_load(filename.c_str(), &width, &height, &channels, 4);
        if (!img) {
            std::cerr << "Failed to load image: " << filename << std::endl;
            exit(1);
        }
        return img;
    }

    static unsigned char* concatenateImages(const std::vector<unsigned char*>& images, const std::vector<int>& widths, const std::vector<int>& heights, int totalWidth, int maxHeight, int overlap) {
        if (totalWidth <= 0 || maxHeight <= 0) {
            std::cerr << "Invalid image size: totalWidth=" << totalWidth << ", maxHeight=" << maxHeight << std::endl;
            return nullptr;
        }

        unsigned char* result = (unsigned char*)malloc(totalWidth * maxHeight * 4);
        memset(result, 0, totalWidth * maxHeight * 4);

        int currentX = 0;
        for (size_t i = 0; i < images.size(); ++i) {
            int width = widths[i];
            int height = heights[i];

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    if (currentX + x >= totalWidth) {
                        std::cerr << "Memory overflow risk at x=" << x << ", y=" << y << ", currentX=" << currentX << ", totalWidth=" << totalWidth << std::endl;
                        continue;
                    }

                    unsigned char* src = &images[i][(y * width + x) * 4];
                    unsigned char* dst = &result[((y) * totalWidth + currentX + x) * 4];

                    dst[0] = src[0];
                    dst[1] = src[1];
                    dst[2] = src[2];
                    dst[3] = src[3];
                }
            }

            if (i == 0)
                currentX += width - (2 * overlap);
            else
                currentX += width - overlap;
        }
        return result;
    }

    static void GenImage(const std::string& inputString, const int index) {
        std::vector<unsigned char*> images;
        std::vector<int> widths, heights;

        int totalWidth = 0;
        int maxHeight = 0;
        int overlap = 1;

        if (inputString.empty()) {
            std::string filename = RESOURCE_DIR"/Text/space.png";
            int width, height, channels;
            unsigned char* img = loadImage(filename, width, height, channels);
            images.push_back(img);
            widths.push_back(width);
            heights.push_back(height);
            totalWidth = width;
            maxHeight = height;
        } else {
            for (char c : inputString) {
                std::string filename = resolvePath(c);
                if (filename.empty()) continue;

                int width, height, channels;
                unsigned char* img = loadImage(filename, width, height, channels);
                images.push_back(img);
                widths.push_back(width);
                heights.push_back(height);

                if (height > maxHeight)
                    maxHeight = height;
            }

            if (!widths.empty()) {
                totalWidth = widths[0];
                for (size_t i = 1; i < widths.size(); ++i) {
                    totalWidth += (widths[i] - overlap);
                }
            }
        }

        if (images.empty()) {
            std::cerr << "No valid images loaded!" << std::endl;
            return;
        }

        unsigned char* result = concatenateImages(images, widths, heights, totalWidth, maxHeight, overlap);
        if (!result) {
            std::cerr << "Image generation failed due to invalid memory allocation." << std::endl;
            return;
        }

        std::string outputDir = RESOURCE_DIR"/TextGenerator";
        std::filesystem::create_directories(outputDir);

        if (index > 0) {
            std::string prevFile = outputDir + "/output" + std::to_string(index - 1) + ".png";
            if (std::filesystem::exists(prevFile)) {
                std::filesystem::remove(prevFile);
                std::cout << "Deleted previous image: " << prevFile << std::endl;
            }
        }

        std::string outputFile = outputDir + "/output" + std::to_string(index) + ".png";
        int success = stbi_write_png(outputFile.c_str(), totalWidth, maxHeight, 4, result, totalWidth * 4);

        if (success)
            std::cout << "Image generated at: " << outputFile << std::endl;
        else
            std::cerr << "Failed to save image!" << std::endl;

        for (auto img : images) {
            stbi_image_free(img);
        }
        free(result);
    }
};

#endif
