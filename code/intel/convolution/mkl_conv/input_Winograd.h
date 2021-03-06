/*******************************************************************************
* Copyright 2017 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <vector>

struct conv_problem {
    int groups;
    int minibatch;
    int w;
    int h;
    int ic;
    int oc;
    int fw;
    int fh;
    int stride;
    int padd;
    int iters;
    const char *name;
};

static const std::vector<conv_problem> conv_problems = {
    /*  /\* DeepBench *\/ */
    /* {1, 16, 480, 48, 1, 16, 3, 3, 1, 1, 1000, "DeepBench"}, */
    /* {1, 8, 224, 224, 3, 64, 3, 3, 1, 1, 1000, "DeepBench"}, */
    /* {1, 16, 224, 224, 3, 64, 3, 3, 1, 1, 1000, "DeepBench"}, */
    /* /\* Topology: alexnet *\/ */
    /* {1, 256, 13, 13, 256, 384, 3, 3, 1, 1, 1000, "alexnet:conv3"}, */
    /* {2, 256, 13, 13, 384, 384, 3, 3, 1, 1, 1000, "alexnet:conv4"}, */
    /* {2, 256, 13, 13, 384, 256, 3, 3, 1, 1, 1000, "alexnet:conv5"}, */
    /* /\* Topology: alexnet-convnet *\/ */
    /* {1, 256, 13, 13, 192, 384, 3, 3, 1, 1, 1000, "alexnet-convnet:conv3"}, */
    /* {2, 256, 13, 13, 384, 256, 3, 3, 1, 1, 1000, "alexnet-convnet:conv4"}, */
    /* {2, 256, 13, 13, 256, 256, 3, 3, 1, 1, 1000, "alexnet-convnet:conv5"}, */
    /* /\* Topology: vgg_19 *\/ */
    /* {1, 64, 224, 224, 3, 64, 3, 3, 1, 1, 1000, "vgg_19:conv1_1"}, */
    /* {1, 64, 224, 224, 64, 64, 3, 3, 1, 1, 1000, "vgg_19:conv1_2"}, */
    {1, 64, 56, 56, 256, 256, 3, 3, 1, 1, 1000, "vgg_19:conv3_3"},
    {1, 64, 56, 56, 256, 256, 3, 3, 1, 1, 1000, "vgg_19:conv3_4"},
    /*  /\* Topology: resnet_50 *\/ */
    {1, 50, 56, 56, 64, 64, 3, 3, 1, 1, 1000, "resnet_50:res2a_branch2b"},
    {1, 50, 56, 56, 64, 64, 3, 3, 1, 1, 1000, "resnet_50:res2b_branch2b"},
    {1, 50, 56, 56, 64, 64, 3, 3, 1, 1, 1000, "resnet_50:res2c_branch2b"},
    {1, 50, 28, 28, 128, 128, 3, 3, 1, 1, 1000, "resnet_50:res3a_branch2b"},
    {1, 50, 28, 28, 128, 128, 3, 3, 1, 1, 1000, "resnet_50:res3b_branch2b"},
    {1, 50, 28, 28, 128, 128, 3, 3, 1, 1, 1000, "resnet_50:res3c_branch2b"},
    {1, 50, 28, 28, 128, 128, 3, 3, 1, 1, 1000, "resnet_50:res3d_branch2b"},
    {1, 50, 14, 14, 256, 256, 3, 3, 1, 1, 1000, "resnet_50:res4a_branch2b"},
    {1, 50, 14, 14, 256, 256, 3, 3, 1, 1, 1000, "resnet_50:res4b_branch2b"},
    {1, 50, 14, 14, 256, 256, 3, 3, 1, 1, 1000, "resnet_50:res4c_branch2b"},
    {1, 50, 14, 14, 256, 256, 3, 3, 1, 1, 1000, "resnet_50:res4d_branch2b"},
    {1, 50, 14, 14, 256, 256, 3, 3, 1, 1, 1000, "resnet_50:res4e_branch2b"},
    {1, 50, 14, 14, 256, 256, 3, 3, 1, 1, 1000, "resnet_50:res4f_branch2b"},
    {1, 50, 7, 7, 512, 512, 3, 3, 1, 1, 1000, "resnet_50:res5a_branch2b"},
    {1, 50, 7, 7, 512, 512, 3, 3, 1, 1, 1000, "resnet_50:res5b_branch2b"},
    {1, 50, 7, 7, 512, 512, 3, 3, 1, 1, 1000, "resnet_50:res5c_branch2b"},
     /* Topology: googlenet_v1 */
    {1, 96, 56, 56, 64, 192, 3, 3, 1, 1, 1000, "googlenet_v1:conv2/3x3"},
    {1, 96, 28, 28, 96, 128, 3, 3, 1, 1, 1000, "googlenet_v1:inception_3a/3x3"},
    {1, 96, 28, 28, 128, 192, 3, 3, 1, 1, 1000, "googlenet_v1:inception_3b/3x3"},
    {1, 96, 14, 14, 96, 208, 3, 3, 1, 1, 1000, "googlenet_v1:inception_4a/3x3"},
    {1, 96, 14, 14, 112, 224, 3, 3, 1, 1, 1000, "googlenet_v1:inception_4b/3x3"},
    {1, 96, 14, 14, 128, 256, 3, 3, 1, 1, 1000, "googlenet_v1:inception_4c/3x3"},
    {1, 96, 14, 14, 144, 288, 3, 3, 1, 1, 1000, "googlenet_v1:inception_4d/3x3"},
    {1, 96, 14, 14, 160, 320, 3, 3, 1, 1, 1000, "googlenet_v1:inception_4e/3x3"},
    {1, 96, 7, 7, 160, 320, 3, 3, 1, 1, 1000, "googlenet_v1:inception_5a/3x3"},
    {1, 96, 7, 7, 192, 384, 3, 3, 1, 1, 1000, "googlenet_v1:inception_5b/3x3"},
     /* Topology: googlenet_v2 */
    {1, 96, 56, 56, 64, 192, 3, 3, 1, 1, 1000, "googlenet_v2:conv2/3x3"},
    {1, 96, 28, 28, 64, 64, 3, 3, 1, 1, 1000, "googlenet_v2:inception_3a/3x3"},
    {1, 96, 28, 28, 64, 96, 3, 3, 1, 1, 1000, "googlenet_v2:inception_3a/double3x3a"},
    {1, 96, 28, 28, 96, 96, 3, 3, 1, 1, 1000, "googlenet_v2:inception_3a/double3x3b"},
    {1, 96, 28, 28, 64, 96, 3, 3, 1, 1, 1000, "googlenet_v2:inception_3b/3x3"},
    {1, 96, 28, 28, 64, 96, 3, 3, 1, 1, 1000, "googlenet_v2:inception_3b/double3x3a"},
    {1, 96, 28, 28, 96, 96, 3, 3, 1, 1, 1000, "googlenet_v2:inception_3b/double3x3b"},
    {1, 96, 28, 28, 64, 96, 3, 3, 1, 1, 1000, "googlenet_v2:inception_3c/double3x3a"},
    {1, 96, 14, 14, 64, 96, 3, 3, 1, 1, 1000, "googlenet_v2:inception_4a/3x3"},
    {1, 96, 14, 14, 96, 128, 3, 3, 1, 1, 1000, "googlenet_v2:inception_4a/double3x3a"},
    {1, 96, 14, 14, 128, 128, 3, 3, 1, 1, 1000, "googlenet_v2:inception_4a/double3x3b"},
    {1, 96, 14, 14, 96, 128, 3, 3, 1, 1, 1000, "googlenet_v2:inception_4b/3x3"},
    {1, 96, 14, 14, 96, 128, 3, 3, 1, 1, 1000, "googlenet_v2:inception_4b/double3x3a"},
    {1, 96, 14, 14, 128, 128, 3, 3, 1, 1, 1000, "googlenet_v2:inception_4b/double3x3b"},
    {1, 96, 14, 14, 128, 160, 3, 3, 1, 1, 1000, "googlenet_v2:inception_4c/3x3"},
    {1, 96, 14, 14, 128, 160, 3, 3, 1, 1, 1000, "googlenet_v2:inception_4c/double3x3a"},
    {1, 96, 14, 14, 160, 160, 3, 3, 1, 1, 1000, "googlenet_v2:inception_4c/double3x3b"},
    {1, 96, 14, 14, 128, 192, 3, 3, 1, 1, 1000, "googlenet_v2:inception_4d/3x3"},
    {1, 96, 14, 14, 160, 192, 3, 3, 1, 1, 1000, "googlenet_v2:inception_4d/double3x3a"},
    {1, 96, 14, 14, 192, 192, 3, 3, 1, 1, 1000, "googlenet_v2:inception_4d/double3x3b"},
    {1, 96, 14, 14, 192, 256, 3, 3, 1, 1, 1000, "googlenet_v2:inception_4e/double3x3a"},
    {1, 96, 7, 7, 192, 320, 3, 3, 1, 1, 1000, "googlenet_v2:inception_5a/3x3"},
    {1, 96, 7, 7, 160, 224, 3, 3, 1, 1, 1000, "googlenet_v2:inception_5a/double3x3a"},
    {1, 96, 7, 7, 224, 224, 3, 3, 1, 1, 1000, "googlenet_v2:inception_5a/double3x3b"},
    {1, 96, 7, 7, 192, 320, 3, 3, 1, 1, 1000, "googlenet_v2:inception_5b/3x3"},
    {1, 96, 7, 7, 192, 224, 3, 3, 1, 1, 1000, "googlenet_v2:inception_5b/double3x3a"},
    {1, 96, 7, 7, 224, 224, 3, 3, 1, 1, 1000, "googlenet_v2:inception_5b/double3x3b"},
};
