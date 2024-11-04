import type {Team} from "@/models/team";

export class Game {
    private readonly _teamOne: Team;
    private readonly _teamTwo: Team;
    private _duration: number = 0; //In seconds
    private readonly _date: Date;

    constructor(teamOne: Team, teamTwo: Team, date: Date) {
        this._teamOne = teamOne;
        this._teamTwo = teamTwo;
        this._date = date;
    }

    get teamOne() {
        return this._teamOne;
    }

    get teamTwo() {
        return this._teamTwo;
    }

    get date() {
        return this._date;
    }

    get duration() {
        return this._duration;
    }

    set duration(value: number) {
        if(value < 0) {
            throw new Error("Duration cannot be negative");
        }

        this._duration = value;
    }
}