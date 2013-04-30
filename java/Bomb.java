
public class Bomb {
   public final int playerId;
   public final int ticksLeft;
   public final int x;
   public final int y;

   public Bomb(int playerId, int ticksLeft, int x, int y) {
      this.playerId = playerId;
      this.ticksLeft = ticksLeft;
      this.x = x;
      this.y = y;
   }
}
