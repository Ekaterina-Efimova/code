package exercise.exercise.di;

import exercise.exercise.datasource.repository.GameStorage;
import exercise.exercise.datasource.repository.GameRepository;
import exercise.exercise.domain.service.GameRepositoryServiseImpl;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class DependencyGraphConfiguration {

	@Bean
	public GameStorage storageRepository() {
		return GameStorage.getInstance();
	}

	@Bean
	public GameRepositoryServiseImpl storageService(GameRepository gameRepository) {
		return new GameRepositoryServiseImpl(gameRepository);
	}

	@Bean
	public GameRepository gameRepository() {
		return new GameRepository();
	}
}