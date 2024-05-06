export default class Team {
    name = "";
    goals = 0;

    constructor(name) {
        this.name = name;
    }

    get Name() {
        return this.name;
    };

    get Goals() {
        return this.goals;
    };

    scoreGoal() {
        this.goals++;
    };
}