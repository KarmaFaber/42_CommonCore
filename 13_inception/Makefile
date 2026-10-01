#◉────▣───▢◇▢───▣────◉•◉───▣───▢   Colors:   ▢───▣───◉•◉───▣────▢◇▢───▣───◉#
GREEN		:= \033[0;32m
YELLOW		:= \033[0;33m
BLUE		:= \033[0;34m
MAGENTA		:= \033[0;35m
RESET		:= \033[0m

#◉───▣───▢◇▢───▣───◉•◉───▣───▢   Variables:   ▢───▣───◉•◉───▣───▢◇▢───▣───◉#
LOGIN		:= mzolotar
DOMAIN		:= $(LOGIN).42.fr

# Paths
DATA_PATH	:= /home/$(LOGIN)/data
WP_DATA		:= $(DATA_PATH)/wordpress_data
DB_DATA		:= $(DATA_PATH)/mariadb_data

export DATA_PATH WP_DATA DB_DATA DOMAIN

# Docker Compose command
# -f flag specifies the path to the configuration file
#sudo -E -> Preserve Environment
DOCKER_COMPOSE	:= sudo -E docker compose -f srcs/docker-compose.yml

#◉───▣───▢◇▢───▣───◉•◉───▣───▢     Rules      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

all: up

# Sudo checker:
check_sudo:
	@echo "$(BLUE) ⌛  Checking sudo privilegies...$(RESET)"
	@sudo -n true 2>/dev/null || ( \
		echo " ❌ [ERROR] Sudo requires password or user is not in sudoers!"; \
		exit 1 \
	)
	@echo "$(GREEN) ✅ Sudo access verified.$(RESET)"

# Build and start containers.
up: check_sudo setup 
	@echo "$(BLUE) ⌛ Starting services ..$(RESET)"
	@$(DOCKER_COMPOSE) up -d --build || ( \
		echo " ❌ [ERROR] Docker Compose failed!"; \
		exit 1; \
	)
	@echo "$(GREEN) ✅ Full infrastructure is up!$(RESET)"

# Stop containers without removing them
stop:
	@echo "$(YELLOW) ⌛ Stopping containers...$(RESET)"
	@$(DOCKER_COMPOSE) stop

# Start previously stopped containers
start:
	@echo "$(GREEN) ⌛ Starting containers...$(RESET)"
	@$(DOCKER_COMPOSE) start

# Stop and remove containers, networks, and images
down:
	@echo "$(MAGENTA) ⌛ Shutting down and removing containers...$(RESET)"
	@$(DOCKER_COMPOSE) down

# Create the necessary folders for volumes on the Host
setup:
	@echo "$(BLUE) ⌛ Setting up data directories at $(DATA_PATH)...$(RESET)"
	@sudo mkdir -p $(WP_DATA) $(DB_DATA)
	@sudo chmod 777 $(DATA_PATH) 

# Check status of containers
status:
	@$(DOCKER_COMPOSE) ps

#Check resource usage of containers
stats:
	@$(DOCKER_COMPOSE) stats --no-stream

# Show logs of all containers
logs:
	@$(DOCKER_COMPOSE) logs -f

# Clean containers and networks
clean: down
	@sudo docker system prune -a
	@echo "$(YELLOW) ⌛ Cleaning containers and networks.$(RESET)"

# Full clean: remove everything including VOLUMES (The most aggressive rule)
fclean: clean
	@sudo rm -rf $(DATA_PATH) 
	@sudo docker volume rm $$(sudo docker volume ls -q) 2>/dev/null || true
	@echo "$(MAGENTA) ✅ Deleted data and volumes.$(RESET)"

re: fclean all

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Phony targets  ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

.PHONY: all check_sudo up stop start down setup status stats logs clean fclean re
