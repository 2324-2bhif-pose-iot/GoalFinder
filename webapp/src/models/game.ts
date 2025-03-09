import type {Player} from "@/models/player";

class Game {
    private readonly players: Player[];

    constructor(name: string) {
        this.players = [];
    }

    public addPlayer(player: Player): void {
        this.players.push(player);
    }

    public removePlayer(player: Player): void {
        this.players.splice(this.players.indexOf(player), 1);
    }
}