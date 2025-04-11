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
    static std::string basePath;

    static void setBasePath(const std::string& path) {
        basePath = path;
    }

    static std::string resolvePath(char c) {
        if (c >= 'a' && c <= 'z') {
            return basePath + "/Text/SmallLetter/" + std::string(1, c) + ".png";
        } else if (c >= 'A' && c <= 'Z') {
            return basePath + "/Text/BigLetter/" + std::string(1, c) + ".png";
        } else if (c >= '0' && c <= '9') {
            return basePath + "/Text/Number/" + std::string(1, c) + ".png";
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
        unsigned char* result = (unsigned char*)malloc(totalWidth * maxHeight * 4);
        memset(result, 0, totalWidth * maxHeight * 4);

        int currentX = 0;
        for (size_t i = 0; i < images.size(); ++i) {
            int width = widths[i];
            int height = heights[i];
            int yOffset = maxHeight - height;

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    unsigned char* src = &images[i][(y * width + x) * 4];
                    unsigned char* dst = &result[((y + yOffset) * totalWidth + currentX + x) * 4];

                    dst[0] = src[0];
                    dst[1] = src[1];
                    dst[2] = src[2];
                    dst[3] = src[3];
                }
            }

            if (currentX != 0)
                currentX += (width - overlap);
            else
                currentX += width - (2 * overlap);
        }
        return result;
    }

    static void GenImage(const std::string& inputString) {
        std::vector<unsigned char*> images;
        std::vector<int> widths, heights;

        int totalWidth = 0;
        int maxHeight = 0;
        int overlap = 2;

        for (char c : inputString) {
            std::string filename = resolvePath(c);
            if (filename.empty()) continue;

            int width, height, channels;
            unsigned char* img = loadImage(filename, width, height, channels);
            images.push_back(img);
            widths.push_back(width);
            heights.push_back(height);

            totalWidth += (width - overlap);
            if (height > maxHeight) {
                maxHeight = height;
            }
        }

        if (images.empty()) {
            std::cerr << "No valid images loaded!" << std::endl;
            return;
        }

        unsigned char* result = concatenateImages(images, widths, heights, totalWidth, maxHeight, overlap);

        std::string outputDir = basePath + "/TextGenerator";
        std::filesystem::create_directories(outputDir);

        std::string outputFile = outputDir + "/output.png";
        int success = stbi_write_png(outputFile.c_str(), totalWidth, maxHeight, 4, result, totalWidth * 4);

        if (success)
            std::cout << "✅ Image generated at: " << outputFile << std::endl;
        else
            std::cerr << "❌ Failed to save image!" << std::endl;

        for (auto img : images) {
            stbi_image_free(img);
        }
        free(result);
    }
};

std::string ImageGenerator::basePath = "../../Resources";

#endif
