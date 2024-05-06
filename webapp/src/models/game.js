import Team from "@/models/team.js";

export default class Game {
    teamOne = null;
    teamTwo = null;
    duration = 0; //In seconds
    date = null;

    constructor(teamOne, teamTwo, date) {
        if(teamOne instanceof Team && teamTwo instanceof Team && date instanceof Date) {
            this.teamOne = teamOne;
            this.teamTwo = teamTwo;
            this.date = date;
        }
    }

    get TeamOne() {
        return this.teamOne;
    }

    get TeamTwo() {
        return this.teamTwo;
    }

    get Date() {
        return this.date;
    }

    get Duration() {
        return this.duration;
    }

    set Duration(value) {
        this.duration = value;
    }
}