import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;


public class Main {
	   public static void main( String[] args ) throws IOException {
	      Logger log = new Logger(System.err, true);
	      BufferedReader in = new Logger.LoggedReader(new InputStreamReader(System.in), log);
	      PrintStream out = new Logger.LoggedWriter(System.out, log);
	      Client client = new Client(in, out, log);
	      client.playGame();
	   }
}
