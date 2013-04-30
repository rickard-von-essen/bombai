
public class BombAction {
   public final int playerId;
   public final BombCommand bombCommand;
   
   public BombAction(int playerId, BombCommand bombCommand) {
      this.playerId = playerId;
      this.bombCommand = bombCommand;
   }
}
