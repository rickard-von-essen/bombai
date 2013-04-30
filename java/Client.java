import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Random;

public class Client {   
   private final Logger log;
   private final PrintStream out;
   private final BufferedReader in;
   private Engine engine;
   private Game game;

   public Client(BufferedReader in, PrintStream out, Logger log) {
      this.in = in;
      this.out = out;
      this.log = log;
   }

   public void playGame() throws IOException {
      initialize();

      GameState currentState = game.getNextState();
      while(!currentState.isFinished()) {
         RoundInfo previousActions = game.getLastRoundsActions();
         log.debug("Creating command in round");
         Command command = engine.playRound(currentState, previousActions);
         writeCommand(command);
         currentState = game.getNextState();
      }
      
      log.debug("Game over detected");
   }

   private void initialize() throws IOException {
      log.debug("Initializing client, waiting for input");
      int playerId        = Integer.parseInt(in.readLine());
      int numberOfPlayers = Integer.parseInt(in.readLine());
      int maxTurns        = Integer.parseInt(in.readLine());
      int boardWidth      = Integer.parseInt(in.readLine());
      int boardHeight     = Integer.parseInt(in.readLine());
      
      log.debug("Player ID: " + playerId + ", Number of players: " + numberOfPlayers + ", Max turns: " +
            maxTurns + ", Board width: " + boardWidth + ", Board height: " + boardHeight);
      
      engine = createEngine(playerId, maxTurns);
      game = createGame(boardWidth, boardHeight, numberOfPlayers);
   }   
   
   private Game createGame(int boardWidth, int boardHeight, int numberOfPlayers) {
      return new Game(boardWidth, boardHeight, numberOfPlayers, in);
   }

   public Engine createEngine(int playerId, int maxTurns) {
      // TODO: Replace this implementation with your own engine implementation
      return new RandomEngine(playerId, maxTurns, new Random(), log);
   }
   
   private void writeCommand(Command command) {
      out.println(command.getRepresentation());
   }
}
