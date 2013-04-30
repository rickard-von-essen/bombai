
public class SimpleAction {
   public final int playerId;
   public final SimpleCommand command;
   
   public SimpleAction(int playerId, SimpleCommand command) {
      this.playerId = playerId;
      this.command = command;
   }
}
