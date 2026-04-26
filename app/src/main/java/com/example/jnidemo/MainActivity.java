package com.example.jnidemo;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    public native String helloFromJNI();
    public native int factorial(int n);
    public native String reverseString(String s);
    public native int sumArray(int[] values);
    public native int[] multiplyMatrices(int[] matrixA, int[] matrixB, int dimension);
    public native boolean containsForbiddenChars(String input);
    public native long nativeBenchmark(int iterations);

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar jungleToolbar = findViewById(R.id.jungleToolbar);
        setSupportActionBar(jungleToolbar);

        TextView jungleGreeting = findViewById(R.id.tvHello);
        TextView jungleFactorial = findViewById(R.id.tvFact);
        TextView jungleEcho = findViewById(R.id.tvReverse);
        TextView jungleTally = findViewById(R.id.tvArray);

        jungleGreeting.setText(helloFromJNI());

        int wildResult = factorial(10);
        int negativeResult = factorial(-5);
        int overflowResult = factorial(20);
        jungleFactorial.setText(
                "factorial(10) = " + wildResult + "\n" +
                        "factorial(-5) = " + negativeResult + "\n" +
                        "factorial(20) = " + overflowResult
        );

        String flippedVine = reverseString("JNI is powerful!");
        String emptyFlip = reverseString("");
        jungleEcho.setText(
                "Reversed: " + flippedVine + "\n" +
                        "Empty reversed: '" + emptyFlip + "'"
        );

        int[] canopyNumbers = {10, 20, 30, 40, 50};
        int jungleSum = sumArray(canopyNumbers);
        int emptySum = sumArray(new int[]{});
        jungleTally.setText(
                "Array sum = " + jungleSum + "\n" +
                        "Empty array sum = " + emptySum
        );

        int[] matA = {1, 2, 3, 4};
        int[] matB = {5, 6, 7, 8};
        int[] matrixProduct = multiplyMatrices(matA, matB, 2);
        TextView jungleMatrix = findViewById(R.id.tvMatrix);
        jungleMatrix.setText(
                "Matrix result: [" +
                        matrixProduct[0] + ", " + matrixProduct[1] + ", " +
                        matrixProduct[2] + ", " + matrixProduct[3] + "]"
        );

        boolean hasDanger = containsForbiddenChars("Hello@World!");
        boolean isClean = containsForbiddenChars("HelloWorld");
        TextView jungleGuard = findViewById(R.id.tvForbidden);
        jungleGuard.setText(
                "Hello@World! forbidden = " + hasDanger + "\n" +
                        "HelloWorld forbidden = " + isClean
        );

        int benchIterations = 1000000;
        long javaBenchStart = System.nanoTime();
        long javaWildSum = 0;
        for (int i = 0; i < benchIterations; i++) javaWildSum += (long) i * i;
        long javaBenchTime = System.nanoTime() - javaBenchStart;

        long nativeBenchStart = System.nanoTime();
        long nativeWildSum = nativeBenchmark(benchIterations);
        long nativeBenchTime = System.nanoTime() - nativeBenchStart;

        TextView jungleBench = findViewById(R.id.tvBenchmark);
        jungleBench.setText(
                "Java time: " + javaBenchTime / 1_000_000 + " ms\n" +
                        "Native time: " + nativeBenchTime / 1_000_000 + " ms"
        );
    }
}