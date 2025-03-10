import type {Player} from "@/models/player";

abstract class Game {
    private readonly _players: Player[];
    private _isRunning: boolean = false;

    constructor() {
        this._players = [];
    }

    public get isRunning(): boolean {
        return this._isRunning;
    }

    public get players(): Player[] {
        return [...this._players];
    }

    public get sortedPlayers() {
        return this._players.slice().sort((a, b) => {
            const diffA = a.hits - a.misses;
            const diffB = b.hits - b.misses;
            return diffB - diffA;
        });
    }

    public addPlayer(player: Player): void {
        if (!this._players.some(p => p.name === player.name)) {
            this._players.push(player);
        }
    }

    public removePlayer(playerIndex: number): void {
        this._players.splice(playerIndex, 1);
    }

    public addHitToPlayer(playerIndex: number): void {
        this._players[playerIndex].addHit();
    }

    public addMissToPlayer(playerIndex: number): void {
        this._players[playerIndex].addMiss();
    }

    public start(): void {
        this._isRunning = true;
    }

    public pause(): void {
        this._isRunning = false;
    }

    public abstract reset(): void;
}

export class ShotChallengeGame extends Game {
    private static readonly PLAY_DURATION: number = 60;

    private _timer: number = 0;
    private timerIntervalId: number = -1;
    private selectedPlayerIndex: number = 0;

    public get timer(): number {
        return this._timer;
    }

    public getSelectedPlayer(): Player {
        return this.players[this.selectedPlayerIndex];
    }

    public constructor() {
        super();
        this.resetTimer();
    }

    public removePlayer(playerIndex: number): void {
        super.removePlayer(playerIndex);

        this.reset();
    }

    public start(): void {
        if(!this.isRunning) {
            this.timerIntervalId = setInterval(() => {
                this._timer--;

                if (this._timer <= 0) {
                    this.resetTimer();
                    this.selectNewPlayer();
                }
            }, 1000);
        }

        super.start();
    }

    public pause(): void {
        clearInterval(this.timerIntervalId);

        super.pause();
    }

    public reset(): void {
        this.selectedPlayerIndex = 0;
        this.pause();
        this.resetTimer();
    }

    private selectNewPlayer(): void {
        this.selectedPlayerIndex++;

        if(this.selectedPlayerIndex >= this.players.length) {
            this.selectedPlayerIndex = 0;
        }
    }

    private resetTimer(): void {
        this._timer = ShotChallengeGame.PLAY_DURATION;
    }
}