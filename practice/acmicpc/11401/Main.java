import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        long N = sc.nextInt();
        long K = sc.nextInt();
 
        long tmp = f(N);
        for (long i = K; i > 0; i--) {
            tmp *= inv(i);
            tmp = mod(tmp);
        }
        for (long i = N - K; i > 0; i--) {
            tmp *= inv(i);
            tmp = mod(tmp);
        }
        System.out.println(tmp);
    }
 
    private static long inv(long k) {
        long[] arr = new long[30];
        arr[0] = k;
        for (int n = 1; n < 30; n++) {
            arr[n] = mod(arr[n - 1] * arr[n - 1]);
        }
        return mod(mod(mod(mod(mod(mod(mod(mod(mod(mod(mod(mod(mod(mod(arr[29] * arr[28]) * arr[27]) * arr[25])
                * arr[24]) * arr[23]) * arr[20]) * arr[19]) * arr[17]) * arr[15]) * arr[14]) * arr[11]) * arr[9]) * arr[2]) * arr[0]);
    }
 
    private static long f(long n) {
        long ans = 1;
        for (long i = n; i > 0; i--) {
            ans *= i;
            ans = mod(ans);
        }
        return ans;
    }
 
    private static long mod(long n) {
        if (n > 1000000007) n %= 1000000007;
        return n;
    }
}
