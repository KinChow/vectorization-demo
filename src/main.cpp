/*
 * @Author: Zhou Zijian
 * @Date: 2024-02-21 01:06:38
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2024-02-21 02:11:46
 */

#include <cstdlib>
#include <cstring>
#include <vector>
#include "config.h"
#include "log.h"
#include "test.h"

static const char *helpStr = "\n " PROJECT_NAME " [OPTIONS]"
                             "\n"
                             "\n OPTIONS:"
                             "\n  --test-1                    run test 1"
                             "\n  --test-2                    run test 2"
                             "\n  --test-3                    run test 3"
                             "\n  --test-4                    run test 4"
                             "\n  --all-tests                 run all above tests [default]"
                             "\n  --size                      size of data"
                             "\n  -v, --version               display version"
                             "\n  -h, --help                  display help message"
                             "\n";

int main(int argc, char *argv[])
{
    bool allTests = true;
    bool isTest1 = false;
    bool isTest2 = false;
    bool isTest3 = false;
    bool isTest4 = false;
    int size = 1024;

    for (int i = 1; i < argc; i++) {
        if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) {
            LOGI("%s", helpStr);
            exit(0);
        } else if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--version") == 0)) {
            LOGI(PROJECT_NAME " version: %d.%d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TWEAK);
            exit(0);
        } else if ((strcmp(argv[i], "--test-1") == 0) ||
            (strcmp(argv[i], "--test-2") == 0) ||
            (strcmp(argv[i], "--test-3") == 0) ||
            (strcmp(argv[i], "--test-4") == 0)) {
            allTests = false;
            if (strcmp(argv[i], "--test-1") == 0) {
                isTest1 = true;
            } else if (strcmp(argv[i], "--test-2") == 0) {
                isTest2 = true;
            } else if (strcmp(argv[i], "--test-3") == 0) {
                isTest3 = true;
            } else if (strcmp(argv[i], "--test-4") == 0) {
                isTest4 = true;
            }
        } else if (strcmp(argv[i], "--all-tests") == 0) {
            allTests = false;
            isTest1 = true;
            isTest2 = true;
            isTest3 = true;
            isTest4 = true;
        } else if (strcmp(argv[i], "--size") == 0) {
            if (i + 1 < argc) {
                size = atoi(argv[i + 1]);
                i++;
            }
        }
        else {
            LOGI("%s", helpStr);
            exit(-1);
        }
    }
    if (allTests) {
        isTest1 = true;
        isTest2 = true;
        isTest3 = true;
        isTest4 = true;
    }

    if (isTest1) {
        std::vector<float> input1(size, 1.0f);
        std::vector<float> input2(size, 2.0f);
        std::vector<float> output(size);
        test1(input1.data(), input2.data(), output.data(), size);
    }

    if (isTest2) {
        std::vector<float> input1(size, 1.0f);
        std::vector<float> input2(size, 2.0f);
        std::vector<float> output(size);
        test2(input1.data(), input2.data(), output.data(), size);
    }

    if (isTest3) {
        std::vector<float> input1(size, 1.0f);
        std::vector<float> input2(size, 2.0f);
        std::vector<float> output(size);
        test3(input1.data(), input2.data(), output.data(), size);
    }

    if (isTest4) {
        std::vector<float> input1(size, 1.0f);
        std::vector<float> input2(size, 2.0f);
        std::vector<float> output(size);
        test4(input1.data(), input2.data(), output.data(), size);
    }
    return 0;
}