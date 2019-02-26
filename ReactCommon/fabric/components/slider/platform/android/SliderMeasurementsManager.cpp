/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "SliderMeasurementsManager.h"

#include <fb/fbjni.h>
#include <react/core/conversions.h>
#include <react/jni/ReadableNativeMap.h>

using namespace facebook::jni;

namespace facebook {
namespace react {

const bool SliderMeasurementsManager::shouldMeasureSlider() const {
  return true;
}

Size SliderMeasurementsManager::measure(
    LayoutConstraints layoutConstraints) const {
  const jni::global_ref<jobject> &fabricUIManager =
      contextContainer_->getInstance<jni::global_ref<jobject>>(
          "FabricUIManager");

  static auto measure =
      jni::findClassStatic("com/facebook/react/fabric/FabricUIManager")
          ->getMethod<jlong(
              jstring,
              ReadableMap::javaobject,
              ReadableMap::javaobject,
              jint,
              jint,
              jint,
              jint)>("measure");

  auto minimumSize = layoutConstraints.minimumSize;
  auto maximumSize = layoutConstraints.maximumSize;
  int minWidth = (int)minimumSize.width;
  int minHeight = (int)minimumSize.height;
  int maxWidth = (int)maximumSize.width;
  int maxHeight = (int)maximumSize.height;

  local_ref<JString> componentName = make_jstring("RCTSlider");

  return yogaMeassureToSize(measure(
      fabricUIManager,
      componentName.get(),
      nullptr,
      nullptr,
      minWidth,
      maxWidth,
      minHeight,
      maxHeight));
}

} // namespace react
} // namespace facebook
