import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'
import EditorView from "@/views/EditorView.vue";

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/home',
      name: 'home',
      component: HomeView
    },
    {
      path: '/',
      name: 'editor',
      component: EditorView
    },
    {
      path: "/index.html",
      redirect: { name: "editor" }
    }
  ]
})

export default router
