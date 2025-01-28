package exercise.exercise.web.controller;

import exercise.exercise.datasource.service.GameRepositoryServiseImpl;
import exercise.exercise.domain.model.Game;
import exercise.exercise.domain.service.TicTacToeService;
import exercise.exercise.web.mapper.GameMapperWeb;
import exercise.exercise.web.model.GameWeb;

import org.springframework.web.bind.annotation.*;
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
    gameRepositoryServiseImpl.saveCurrentGame(GameMapperWeb.toDomain(newGame));
    model.addAttribute("game", newGame);
    return "game";
  }

  @PostMapping("/{gameId}")
  public String makeMove(@PathVariable("gameId") UUID gameId, @Autowired GameWeb gameWeb, Model model) {
    Game game = gameRepositoryServiseImpl.findGameById(gameId);
    model.addAttribute("game", GameMapperWeb.toWeb(ticTacToeService.getNextMove(game, gameWeb)));
    gameRepositoryServiseImpl.saveCurrentGame(game);
    return "game";
  }

}
