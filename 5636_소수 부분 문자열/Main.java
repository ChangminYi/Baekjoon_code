import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;

public class Main {
    public static Scanner scanner = new Scanner(System.in);
    public static String str;
    public static ArrayList<Integer> primes = new ArrayList<Integer>(Arrays.asList(2));
    public static boolean is_prime[] = new boolean[1000001];

    public static void init_primes(){
        Arrays.fill(is_prime, false);
        is_prime[2] = true;

        for(int i = 3; i <= 100000; i += 2){
            boolean is_divided = false;

            for(int j = 0; primes.get(j) <= Math.sqrt(i); j++){
                if(i % primes.get(j) == 0){
                    is_divided = true;
                    break;
                }
            }

            if(!is_divided){
                is_prime[i] = true;
                primes.add(i);
            }
        }
    }

    public static void main(String[] args) {
        init_primes();

        while(true){
            str = scanner.nextLine();

            if(str.equals("0")){
                break;
            }
            else{
                int max_prime = 0;

                for(int i = 0, tmp; i < 5; i++){
                    for(int j = 0; j < str.length() - i; j++){
                        tmp = Integer.parseInt(str.substring(j, j + i + 1));

                        if(is_prime[tmp]){
                            max_prime = Math.max(max_prime, tmp);
                        }
                    }
                }

                System.out.println(max_prime);
            }
        }
    }
}
