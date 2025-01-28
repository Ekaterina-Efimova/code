package exercise.exercise.di;

import exercise.exercise.datasource.repository.GameStorage;
import exercise.exercise.datasource.service.GameRepositoryServiseImpl;
import exercise.exercise.domain.service.TicTacToeServiceImpl;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class DependencyGraphConfiguration {

	@Bean
	public GameStorage gameStorage() {
		return GameStorage.getInstance();
	}

	@Bean
	public GameRepositoryServiseImpl gameRepositoryServiseImpl(GameStorage gameStorage) {
		return new GameRepositoryServiseImpl(gameStorage);
	}

	@Bean
	public TicTacToeServiceImpl ticTacToeServiceImpl() {
		return new TicTacToeServiceImpl();
	}
}