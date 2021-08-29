import java.util.Scanner;

public class main {
  public static char toCorrect(char c) {
    char temp = 0;

    switch (c) {
    case 'W': temp = 'Q'; break;
    case 'E': temp = 'W'; break;
    case 'R': temp = 'E'; break;
    case 'T': temp = 'R'; break;
    case 'Y': temp = 'T'; break;
    case 'U': temp = 'Y'; break;
    case 'I': temp = 'U'; break;
    case 'O': temp = 'I'; break;
    case 'P': temp = 'O'; break;
    case '[': temp = 'P'; break;
    case ']': temp = '['; break;
    case '\\': temp = ']'; break;
    case 'S': temp = 'A'; break;
    case 'D': temp = 'S'; break;
    case 'F': temp = 'D'; break;
    case 'G': temp = 'F'; break;
    case 'H': temp = 'G'; break;
    case 'J': temp = 'H'; break;
    case 'K': temp = 'J'; break;
    case 'L': temp = 'K'; break;
    case ';': temp = 'L'; break;
    case '\'': temp = ';'; break;
    case 'X': temp = 'Z'; break;
    case 'C': temp = 'X'; break;
    case 'V': temp = 'C'; break;
    case 'B': temp = 'V'; break;
    case 'N': temp = 'B'; break;
    case 'M': temp = 'N'; break;
    case ',': temp = 'M'; break;
    case '.': temp = ','; break;
    case '/': temp = '.'; break;
    case ' ': temp = ' '; break;
    case '\n': temp = '\n'; break;
    }

    return temp;
  }
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    String temp;
    
    while(scanner.hasNext()) {
      temp = scanner.nextLine();
      
      System.out.println();
    }
    
    scanner.close();
    return;
  }

}
