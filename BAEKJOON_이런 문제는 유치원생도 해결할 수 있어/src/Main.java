import java.util.Scanner;

public class Main {
    public static Scanner scanner = new Scanner(System.in);

    public static boolean Set(String args) {
        if(!args.isEmpty()) {
            if(args.charAt(0) == '{' && args.charAt(args.length() - 1) == '}') {
                return ElementList(args.substring(1, args.length() - 1));
            }
        }
        return false;
    }

    public static boolean ElementList(String args) {
        if(!args.isEmpty()) {
            return List(args);
        }
        return true;
    }

    public static boolean List(String args) {
        if(!args.isEmpty()) {
            if(args.length() == 1) {
                return Atom(args);
            }
            else {
                if(args.charAt(0) == ',') {
                    int ind = args.indexOf(",", 1);
                    if(ind != 1) {
                        return false;
                    }
                    else {
                        return List(args.substring(2));
                    }
                }
                else {
                    int ind = args.indexOf(",");
                    if(ind == -1) {
                        return Set(args);
                    }
                    else {
                        return (Atom(args.substring(0, ind)) || Set(args.substring(0, ind))) && List(args.substring(ind + 1));
                    }
                }
            }
        }
        return false;
    }

    public static boolean Atom(String args) {
        if(args.length() == 1) {
            if(args.equals("{") || args.equals("}") || args.equals(",")) {
                return true;
            }
            else {
                return false;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        int num = scanner.nextInt();
        for(int i = 1; i <= num; i++) {
            String language = scanner.next();
            System.out.print("Word #" + i + ": ");
            if(Set(language)){
                System.out.print("Set\n");
            }
            else{
                System.out.print("No Set\n");
            }
        }

        scanner.close();
    }
}
