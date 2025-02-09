package exercise.exercise.web.controller;

import exercise.exercise.di.DependencyGraphConfiguration;
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
  private final DependencyGraphConfiguration context;

  public GameController() {
    context = new DependencyGraphConfiguration();
  }

  @PostMapping("/new")
  public String newGame(Model model) {
    GameWeb newGame = new GameWeb();
    context.gameRepositoryService().saveCurrentGame(GameMapperWeb.toDomain(newGame));
    model.addAttribute("game", newGame);
    model.addAttribute("isGameActive", true);
    return "game";
  }

  @GetMapping("/new")
  public String showGame(Model model, @Autowired GameWeb gameWeb) {
    model.addAttribute("game", gameWeb);
    model.addAttribute("isGameActive", false); 
    return "game";
  }

  @PostMapping("/{gameId}")
  public String makeMove(@PathVariable("gameId") UUID gameId, @Autowired GameWeb gameWeb, Model model) {
    model.addAttribute("game", GameMapperWeb.toWeb(context.gameRepositoryService().saveCurrentGame(context
        .ticTacToeService().getNextMove(context.gameRepositoryService().findGameById(gameId), gameWeb.getMove()))));
    model.addAttribute("isGameActive", true);
    return "game";
  }
}
