package exercise.exercise.di;

import exercise.exercise.datasource.repository.GameStorage;
import exercise.exercise.datasource.service.GameRepositoryService;
import exercise.exercise.domain.service.TicTacToeService;
import exercise.exercise.datasource.service.GameRepositoryServiceImpl;
import exercise.exercise.domain.service.TicTacToeServiceImpl;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;


@Configuration
@ComponentScan(basePackages = "exercise.exercise")
public class DependencyGraphConfiguration {
	private TicTacToeService ticTacToeService;
	private GameRepositoryService gameRepositoryService;

	public DependencyGraphConfiguration(){
		ticTacToeService = new TicTacToeServiceImpl();
		gameRepositoryService = new GameRepositoryServiceImpl(gameStorage());
	}

	public GameStorage gameStorage() {
		return GameStorage.getInstance();
	}

	public GameRepositoryService gameRepositoryService(){
		return gameRepositoryService;
	}

	public TicTacToeService ticTacToeService() {
		return ticTacToeService;
	}
}