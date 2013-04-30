public class BombCommand implements Command {
   public static final int MIN_TICKS = 5;
   public static final int MAX_TICKS = 25;
   public static final int MAX_BOMBS = 5;
   
   private final int ticks;

   public BombCommand(int ticks) {
      this.ticks = ticks;
   }

   public int getTicks() {
      return ticks;
   }
   
   public String getRepresentation() {
      return Integer.toString(ticks);
   }
}
