<script setup>

</script>

<template>
  <div class="container">
    <h1>Goal Finder Dashboard</h1>
    <div class="row" id="card-container">
      <!--<Card class="col-sm-6 dashboard-card">
        <template #title>{{ $t("header.game_card") }}</template>
        <template #content>
          <p class="m-0">
            Create a new basketball game
          </p>
          <router-link to="/games">
            <Button class="mt-3">
              {{ $t("word.open") }}
            </Button>
          </router-link>
        </template>
      </Card>-->
      <Card class="col-sm-6 dashboard-card">
        <template #title>{{ $t("header.settings_card") }}</template>
        <template #content>
          <p class="m-0">
            {{ $t("description.settings_description") }}
          </p>
          <router-link to="/settings">
            <Button class="mt-3">
              {{ $t("word.open") }}
            </Button>
          </router-link>
        </template>
      </Card>
      <Card class="col-sm-6 dashboard-card">
        <template #title>{{ $t("header.sessions_card") }}</template>
        <template #content>
          <p class="m-0">
            {{ $t("description.sessions_description") }}
          </p>
          <router-link to="/list">
            <Button class="mt-3">
              {{ $t("word.open") }}
            </Button>
          </router-link>
        </template>
      </Card>
    </div>
  </div>
</template>

<style scoped>
  #card-container {
    display: flex;
    gap: 0.3rem;
    flex-wrap: wrap;
    justify-content: center;
    align-items: center;
  }

  .dashboard-card {
    width: 49%;
  }

  .dashboard-card p {
    height: 40%
  }
</style>