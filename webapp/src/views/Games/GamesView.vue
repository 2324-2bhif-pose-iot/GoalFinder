<script setup lang="ts">
import Button from "@/components/Button.vue";
import Page from "@/components/Page.vue";
import Card from "@/components/Card.vue";
</script>

<template>
  <Page :title="$t('header.games')">
    <p>{{ $t("description.gameModes_description") }}</p>
    <div id="card-container">
      <Card class="quick-link">
        <div>
          <h2>{{ $t("header.game_shot_challenge") }}</h2>
          <RouterLink to="/games/shot-challenge"><Button primary>{{ $t("word.open") }}</Button></RouterLink>
        </div>
      </Card>
    </div>

    <div id="timed-shots-challenge">
      <Card class="quick-link">
        <div>
          <h2>{{ $t("header.game_timed_shots_challenge") }}</h2>
          <RouterLink to="/games/timed-shots-challenge"><Button primary>{{ $t("word.open") }}</Button></RouterLink>
        </div>
      </Card>
    </div>
  </Page>
</template>

<style>
#timed-shots-challenge {
    margin-top: 1rem;
}
</style>

