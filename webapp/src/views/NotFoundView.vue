<script setup>

</script>

<template>
  <div class="container" id="root">
    <Card class="mt-5">
      <template #content>
        <h1 class="text-center">404</h1>
        <h2 class="text-center">Seite nicht gefunden</h2>
        <router-link class="btn btn-primary btn-lg w-100 mt-5" to="/">
          <Button>Zurück zur Startseite</Button>
        </router-link>
      </template>
    </Card>
    <div>

    </div>
  </div>
</template>

<style scoped>
  #root {
    display: flex;
    justify-content: center;
  }
</style>