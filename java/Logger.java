import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintStream;
import java.io.Reader;

/**
 * Very simple logger. printing to whatever PrintStream is given to it if debug is enabled.
 */
public class Logger {
   private final PrintStream target;
   private final boolean debug;

   public Logger(PrintStream target, boolean debug) {
      this.target = target;
      this.debug = debug;
   }
   
   public void debug(String message) {
      if(debug) {
         target.println(message);
      }
   }
   
   public static class LoggedReader extends BufferedReader {
      private final Logger log;

      public LoggedReader(Reader in, Logger log) {
         super(in);
         this.log = log;
      }
      
      @Override
      public String readLine() throws IOException {
         String in = super.readLine();
         log.debug("In: " + in);
         return in;
      }      
   }
   
   public static class LoggedWriter extends PrintStream {
      private final Logger log;

      public LoggedWriter(PrintStream out, Logger log) {
         super(out);
         this.log = log;
      }
      
      @Override
      public void println(String out) {
         log.debug("Out: " + out);
         super.println(out);
      }
   }
}
