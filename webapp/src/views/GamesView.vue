<script setup lang="ts">
import Page from "@/components/Page.vue";
import Button from "@/components/Button.vue";
import {Player} from "@/models/Player";
import InputForm from "@/components/InputForm.vue";
import {computed, reactive, ref} from "vue";

let players = ref([] as Player[]);
let showLeaderboard = ref(false);

let newPlayerName = ref("");

function addPerson() {
  if (newPlayerName.value) {
    players.value.push(new Player(newPlayerName.value));
    newPlayerName.value = "";
  }
}

function recordShot(index: number, isHit: boolean) {
  if (isHit) {
    players.value[index].addHit()
  } else {
    players.value[index].addMiss();
  }
}

function removePerson(index: number) {
  players.value.splice(index, 1);
}

function finish() {
  showLeaderboard.value = true;
}

function restart() {
  showLeaderboard.value = false;
  players.value = [];
}

const sortedPersons = computed(() => {
  return players.value.slice().sort((a, b) => {
    const diffA = a.hits - a.misses;
    const diffB = b.hits - b.misses;
    return diffB - diffA;
  })});

</script>

<template>
  <Page :title="$t('header.game')">
    <div class="basketball-shot-tracker" v-if="!showLeaderboard">
      <form @submit.prevent="addPerson">
        <div>
          <label for="personName">{{ $t("word.add_person") }}</label>
          <InputForm id="personName" v-model="newPlayerName"/>
        </div>
        <Button type="submit" primary>{{ $t("word.add_person") }}</Button>
      </form>

      <div v-if="players.length">
        <h3>{{ $t("word.person_list") }}</h3>
        <ul>
          <li v-for="(person, index) in players" :key="index">
            <span>{{ person.name }}</span>
            <div class="buttons-container">
              <Button @click="recordShot(index, true)">{{ $t("word.hit") }}</Button>
              <Button @click="recordShot(index, false)" severity="warning">{{ $t("word.miss") }}</Button>
              <Button @click="removePerson(index)" severity="danger">{{ $t("word.remove") }}</Button>
            </div>
          </li>
        </ul>
      </div>

      <div v-if="players.length">
        <h3>{{ $t("word.results") }}</h3>
        <ul>
          <li v-for="(person, index) in players" :key="index">
            <strong>{{ person.name }}</strong> - {{ $t("word.hits") }}: {{ person.hits }}, {{ $t("word.misses") }}: {{ person.misses }}
          </li>
        </ul>
      </div>

      <div v-if="players.length">
        <Button @click="finish">{{ $t("word.finish") }}</Button>
      </div>
    </div>

    <div class="leaderboard" v-else>
      <h2>{{ $t("word.leaderboard") }}</h2>
      <ul>
        <li v-for="(person, index) in sortedPersons" :key="index"> <!-- This should be sorted persons -->
          <strong>{{ index + 1 }}. {{ person.name }}</strong> - {{ $t("word.hits") }}: {{ person.hits }}, {{ $t("word.misses") }}: {{ person.misses }}
        </li>
      </ul>
      <Button @click="restart">{{ $t("word.restart") }}</Button>
    </div>
  </Page>
</template>

<style scoped>
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