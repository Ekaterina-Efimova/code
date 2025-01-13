package exercise.exercise.web.controller;

import exercise.exercise.domain.model.Game;
import exercise.exercise.domain.service.GameRepositoryServiseImpl;
import exercise.exercise.domain.service.TicTacToeService;
import exercise.exercise.web.mapper.GameMapperWeb;
import exercise.exercise.web.model.GameWeb;

import org.springframework.web.bind.annotation.*;
import org.springframework.web.context.annotation.SessionScope;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.UUID;

@Controller
@RequestMapping("/game")
public class GameController {
  private final TicTacToeService ticTacToeService;
  private final GameRepositoryServiseImpl gameRepositoryServiseImpl;

  public GameController(TicTacToeService ticTacToeService, GameRepositoryServiseImpl gameRepositoryServiseImpl) {
    this.ticTacToeService = ticTacToeService;
    this.gameRepositoryServiseImpl = gameRepositoryServiseImpl;
  }

  @GetMapping("/new")
  public String showGame(Model model) {
    GameWeb newGame = new GameWeb();
    Game game = GameMapperWeb.toDomain(newGame);
    gameRepositoryServiseImpl.saveCurrentGame(game);
    model.addAttribute("game", newGame);
    return "game";
  }

  @PostMapping("/{gameId}")
  @SessionScope
  public String makeMove(@PathVariable("gameId") UUID gameId, @Autowired GameWeb gameWeb, Model model) {
    Game game = gameRepositoryServiseImpl.findGameById(gameId);
    if (game == null) {
      gameWeb.setError("Игра с указанным ID не найдена");

    } else {
      gameStep(game, gameWeb);
      gameRepositoryServiseImpl.saveCurrentGame(game);
      model.addAttribute("game", GameMapperWeb.toWeb(game));
    }

    return "game";
  }

  private void gameStep(Game game, GameWeb gameWeb) {
    if (!ticTacToeService.validateBoard(game.getBoard().getBoard(), gameWeb.getBoard().getBoard())) 
      gameWeb.setError("Некорректное поле");
    
    game.setMove(gameWeb.getPlayerMove());
    if (!ticTacToeService.isGameOver(game.getBoard().getBoard())) {
      ticTacToeService.getNextMove(game);
    }

    if (ticTacToeService.isGameOver(game.getBoard().getBoard()) || game.getError() != null)
      game.setGameOver(true);
  }
}
