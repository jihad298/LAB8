#include <jni.h>
#include <string>
#include <algorithm>
#include <climits>
#include <android/log.h>

#define LOG_TAG "JNI_DEMO"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_helloFromJNI(
        JNIEnv* env,
        jobject) {

    LOGI("helloFromJNI called from native");
    return env->NewStringUTF("Hello from C++ via JNI !");
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_factorial(
        JNIEnv* env,
        jobject,
        jint n) {

    if (n < 0) {
        LOGE("Error: negative input");
        return -1;
    }

    long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
        if (fact > INT_MAX) {
            LOGE("Overflow detected for n=%d", n);
            return -2;
        }
    }

    LOGI("Factorial of %d computed in native = %lld", n, fact);
    return static_cast<jint>(fact);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_reverseString(
        JNIEnv* env,
        jobject,
        jstring javaString) {

    if (javaString == nullptr) {
        LOGE("Null string received");
        return env->NewStringUTF("Error: null string");
    }

    const char* chars = env->GetStringUTFChars(javaString, nullptr);
    if (chars == nullptr) {
        LOGE("Cannot read Java string");
        return env->NewStringUTF("JNI Error");
    }

    std::string s(chars);
    env->ReleaseStringUTFChars(javaString, chars);

    std::reverse(s.begin(), s.end());

    LOGI("Reversed string = %s", s.c_str());
    return env->NewStringUTF(s.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_sumArray(
        JNIEnv* env,
        jobject,
        jintArray array) {

    if (array == nullptr) {
        LOGE("Null array");
        return -1;
    }

    jsize len = env->GetArrayLength(array);
    jint* elements = env->GetIntArrayElements(array, nullptr);

    if (elements == nullptr) {
        LOGE("Cannot access array elements");
        return -2;
    }

    long long sum = 0;
    for (jsize i = 0; i < len; i++) {
        sum += elements[i];
    }

    env->ReleaseIntArrayElements(array, elements, 0);

    if (sum > INT_MAX) {
        LOGE("Sum overflow");
        return -3;
    }

    LOGI("Array sum = %lld", sum);
    return static_cast<jint>(sum);
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_jnidemo_MainActivity_multiplyMatrices(
        JNIEnv* env,
        jobject,
        jintArray matrixA,
        jintArray matrixB,
        jint dimension) {

    jint* canopyA = env->GetIntArrayElements(matrixA, nullptr);
    jint* canopyB = env->GetIntArrayElements(matrixB, nullptr);

    int wildSize = dimension * dimension;
    jintArray jungleResult = env->NewIntArray(wildSize);
    jint* canopyResult = env->GetIntArrayElements(jungleResult, nullptr);

    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            long long cellSum = 0;
            for (int k = 0; k < dimension; k++) {
                cellSum += canopyA[row * dimension + k] * canopyB[k * dimension + col];
            }
            canopyResult[row * dimension + col] = static_cast<jint>(cellSum);
        }
    }

    env->ReleaseIntArrayElements(matrixA, canopyA, 0);
    env->ReleaseIntArrayElements(matrixB, canopyB, 0);
    env->ReleaseIntArrayElements(jungleResult, canopyResult, 0);

    LOGI("Matrix multiplication completed");
    return jungleResult;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_jnidemo_MainActivity_containsForbiddenChars(
        JNIEnv* env,
        jobject,
        jstring inputVine) {

    if (inputVine == nullptr) {
        LOGE("Null string in forbidden check");
        return JNI_TRUE;
    }

    const char* wildChars = env->GetStringUTFChars(inputVine, nullptr);
    if (wildChars == nullptr) return JNI_TRUE;

    std::string jungleText(wildChars);
    env->ReleaseStringUTFChars(inputVine, wildChars);

    std::string forbiddenThicket = "!@#$%^&*<>";
    for (char canopyChar : jungleText) {
        if (forbiddenThicket.find(canopyChar) != std::string::npos) {
            LOGE("Forbidden character detected: %c", canopyChar);
            return JNI_TRUE;
        }
    }

    LOGI("String is clean: %s", jungleText.c_str());
    return JNI_FALSE;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_jnidemo_MainActivity_nativeBenchmark(
        JNIEnv* env,
        jobject,
        jint iterations) {

    long long wildSum = 0;
    for (int i = 0; i < iterations; i++) {
        wildSum += i * i;
    }
    LOGI("Native benchmark sum = %lld", wildSum);
    return static_cast<jlong>(wildSum);
}

static JNINativeMethod jungleRegistry[] = {
        {"helloFromJNI",           "()Ljava/lang/String;",            (void*)Java_com_example_jnidemo_MainActivity_helloFromJNI},
        {"factorial",              "(I)I",                             (void*)Java_com_example_jnidemo_MainActivity_factorial},
        {"reverseString",          "(Ljava/lang/String;)Ljava/lang/String;", (void*)Java_com_example_jnidemo_MainActivity_reverseString},
        {"sumArray",               "([I)I",                            (void*)Java_com_example_jnidemo_MainActivity_sumArray},
        {"multiplyMatrices",       "([I[II)[I",                        (void*)Java_com_example_jnidemo_MainActivity_multiplyMatrices},
        {"containsForbiddenChars", "(Ljava/lang/String;)Z",            (void*)Java_com_example_jnidemo_MainActivity_containsForbiddenChars},
        {"nativeBenchmark",        "(I)J",                             (void*)Java_com_example_jnidemo_MainActivity_nativeBenchmark},
};

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM* jungleVM, void*) {
    JNIEnv* env;
    if (jungleVM->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    jclass wildClass = env->FindClass("com/example/jnidemo/MainActivity");
    env->RegisterNatives(wildClass, jungleRegistry, 7);
    LOGI("JNI_OnLoad: jungle natives registered");
    return JNI_VERSION_1_6;
}