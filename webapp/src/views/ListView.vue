<template>
  <div class="basketball-shot-tracker" v-if="!showLeaderboard">
    <h2>{{ $t("word.basketball_shot_tracker") }}</h2>
    <form @submit.prevent="addPerson">
      <div>
        <label for="personName">{{ $t("word.add_person") }}</label>
        <input type="text" id="personName" v-model="newPerson.name" required />
      </div>
      <Button type="submit">{{ $t("word.add_person") }}</Button>
    </form>

    <div v-if="persons.length">
      <h3>{{ $t("word.person_list") }}</h3>
      <ul>
        <li v-for="(person, index) in persons" :key="index">
          <span>{{ person.name }}</span>
          <div class="buttons-container">
            <Button @click="recordShot(index, true)">{{ $t("word.hit") }}</Button>
            <Button @click="recordShot(index, false)" severity="warn">{{ $t("word.miss") }}</Button>
            <Button @click="removePerson(index)" severity="danger">{{ $t("word.remove") }}</Button>
          </div>
        </li>
      </ul>
    </div>

    <div v-if="persons.length">
      <h3>{{ $t("word.results") }}</h3>
      <ul>
        <li v-for="(person, index) in persons" :key="index">
          <strong>{{ person.name }}</strong> - {{ $t("word.hits") }}: {{ person.hits }}, {{ $t("word.misses") }}: {{ person.misses }}
        </li>
      </ul>
    </div>

    <div v-if="persons.length">
      <Button @click="finish">{{ $t("word.finish") }}</Button>
    </div>
  </div>

  <div class="leaderboard" v-else>
    <h2>{{ $t("word.leaderboard") }}</h2>
    <ul>
      <li v-for="(person, index) in sortedPersons" :key="index">
        <strong>{{ index + 1 }}. {{ person.name }}</strong> - {{ $t("word.hits") }}: {{ person.hits }}, {{ $t("word.misses") }}: {{ person.misses }}
      </li>
    </ul>
    <Button @click="restart">{{ $t("word.restart") }}</Button>
  </div>
</template>

<script>
export default {
  data() {
    return {
      newPerson: {
        name: ''
      },
      persons: [],
      showLeaderboard: false
    };
  },
  methods: {
    addPerson() {
      if (this.newPerson.name.trim() !== '') {
        this.persons.push({ name: this.newPerson.name, hits: 0, misses: 0 });
        this.newPerson.name = '';
      }
    },
    recordShot(index, isHit) {
      if (isHit) {
        this.persons[index].hits++;
      } else {
        this.persons[index].misses++;
      }
    },
    removePerson(index) {
      this.persons.splice(index, 1);
    },
    finish() {
      this.showLeaderboard = true;
    },
    restart() {
      this.showLeaderboard = false;
      this.persons = [];
    }
  },
  computed: {
    sortedPersons() {
      return this.persons.slice().sort((a, b) => {
        const diffA = a.hits - a.misses;
        const diffB = b.hits - b.misses;
        return diffB - diffA;
      });
    }
  }
};
</script>

<style scoped>
.basketball-shot-tracker, .leaderboard {
  max-width: 500px;
  margin: 0 auto;
  padding: 20px;
  border: 1px solid #ddd;
  border-radius: 8px;
}

.basketball-shot-tracker h2, .basketball-shot-tracker h3, .leaderboard h2 {
  text-align: center;
}

.basketball-shot-tracker form div {
  margin-bottom: 15px;
}

.basketball-shot-tracker form label {
  display: block;
  margin-bottom: 5px;
}

.basketball-shot-tracker form input {
  width: 100%;
  padding: 8px;
  box-sizing: border-box;
}

.basketball-shot-tracker ul, .leaderboard ul {
  list-style-type: none;
  padding: 0;
}

.basketball-shot-tracker li, .leaderboard li {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 10px;
}

.buttons-container {
  display: flex;
  gap: 10px;
}
</style>
